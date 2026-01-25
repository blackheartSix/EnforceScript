modded class SCR_BaseScoringSystemComponent
{
	override void AddSuicide(int playerId, int count = 1)
	{
		super.AddSuicide(playerId, count); // calls the original method
		AudioSystem.PlaySound("{E89D9A1F4BA63CDC}Sounds/Props/Furniture/Piano/Samples/Props_Piano_Jingle_1.wav"); // plays a sound - hardcoded here for example purpose
	}
}