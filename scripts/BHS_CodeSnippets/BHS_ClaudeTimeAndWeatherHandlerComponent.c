class BHS_TimeAndWeatherHandlerComponentClass : SCR_TimeAndWeatherHandlerComponentClass
{
}

class BHS_TimeAndWeatherHandlerComponent : SCR_TimeAndWeatherHandlerComponent
{
    //[Attribute(defvalue: "15", UIWidgets.EditBox, desc: "Day (1-31)", category:"Date")]
	[Attribute(defvalue: "1", UIWidgets.Slider, desc: "Day", params: "1 28", category:"Date")]
    protected int m_iDayCorrect;
    
    override void OnWorldPostProcess(World world)
    {
        super.OnWorldPostProcess(world);
        
        if (!Replication.IsServer() || !GetGame().InPlayMode())
            return;
        
        // Override the date with your correct day value
        if (m_bDateOverride)
            SetupDate(m_iDayCorrect, m_iMonth, m_iYear);
    }
}