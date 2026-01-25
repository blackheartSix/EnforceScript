modded class SCR_ScoringSystemComponent //declares which class is being modded
{
	override int CalculateScore(SCR_ScoreInfo info) //declares a method replacing an existing one
	{
		int score = info.m_iKills 		* m_iKillScoreMultiplier +
			info.m_iTeamKills 	* m_iTeamKillScoreMultiplier +
			info.m_iDeaths		* 10 +
			info.m_iSuicides 	* 10 +
			info.m_iObjectives 	* m_iObjectiveScoreMultiplier;
		
		if (score < 0)
			return 0;
		
		return score;
	}
}