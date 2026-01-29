modded class SCR_CampaignBuildingManagerComponent
{
	override protected void OnEntityCoreBudgetUpdated(EEditableEntityBudget entityBudget, int originalBudgetValue, int budgetChange, int updatedBudgetValue, SCR_EditableEntityComponent entity)
	{
		if (IsProxy())
			return;

		if (entityBudget != m_BudgetType)
			return;

		// Continue with compositions placed in WB only when refund is about to happen.
		if (entity.GetOwner().IsLoaded() && budgetChange > 0)
			return;

		// ** OVERRIDE REMOVED **
		//CampaignBuildingManagerComponent should not do anything if there is no campaign
        //const SCR_GameModeCampaign campaign = SCR_GameModeCampaign.GetInstance();
		//if (!campaign)
		//	return;

		// Do not react to changes during loading of session
		if (SCR_PersistenceSystem.IsLoadInProgress())
			return; 

		int propBudgetValue;
		array<ref SCR_EntityBudgetValue> budgets = {};
		entity.GetEntityAndChildrenBudgetCost(budgets);

		//get props budget value
		foreach (SCR_EntityBudgetValue budget : budgets)
		{
			if (budget.GetBudgetType() != EEditableEntityBudget.PROPS)
				continue;

			propBudgetValue = budget.GetBudgetValue();
			break;
		}

		IEntity entityOwner = entity.GetOwnerScripted();
		SCR_ResourceComponent resourceComponent;
		bool wasContainerSpawned;

		// If resource component was not found on deconstruction, spawn a custom one , find again the resource component at this spawned box and fill it with refund supply.
		if (!GetResourceComponent(entityOwner, resourceComponent))
		{
			//Spawn a resource holder only when the refunded object is a composition.
			SCR_CampaignBuildingCompositionComponent compositionComponent = SCR_CampaignBuildingCompositionComponent.Cast(entityOwner.FindComponent(SCR_CampaignBuildingCompositionComponent));
			if (compositionComponent && budgetChange < 0)
			{
				SpawnCustomResourceHolder(entityOwner, resourceComponent);
				wasContainerSpawned = true;
			}
		}

		if (!resourceComponent)
			return;

		//~ Supplies not enabled so no need to remove any
		if (!resourceComponent.IsResourceTypeEnabled())
			return;

		IEntity providerEntity = resourceComponent.GetOwner();

		if (!providerEntity)
			return;

		SCR_CampaignBuildingProviderComponent providerComponent = SCR_CampaignBuildingProviderComponent.Cast(providerEntity.FindComponent(SCR_CampaignBuildingProviderComponent));

		if (budgetChange < 0)
		{
			budgetChange = Math.Round(budgetChange * m_iCompositionRefundPercentage * 0.01);

			if (providerComponent)
				providerComponent.AddPropValue(-propBudgetValue);

			if (wasContainerSpawned)
			{
				SCR_ResourceContainer container = resourceComponent.GetContainer(EResourceType.SUPPLIES);

				if (container)
					container.SetResourceValue(-budgetChange);
			}
			else
			{
				SCR_ResourceGenerator generator = resourceComponent.GetGenerator(EResourceGeneratorID.DEFAULT, EResourceType.SUPPLIES);

				if (generator)
					generator.RequestGeneration(-budgetChange);
			}
		}
		else
		{
			if (providerComponent)
				providerComponent.AddPropValue(propBudgetValue);

			SCR_ResourceConsumer consumer = resourceComponent.GetConsumer(EResourceGeneratorID.DEFAULT, EResourceType.SUPPLIES);

			if (consumer)
				consumer.RequestConsumtion(budgetChange);
		}
	}
}
