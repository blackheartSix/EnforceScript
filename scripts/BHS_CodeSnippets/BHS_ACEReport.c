//Print only the soldiers with health above 50 from two arrays (names and health values).
array<string> soldierNames = { "Allen", "Bradley", "Charles", "Dickens" };
array<int> healthValues = { 45, 60, 80, 15 };
foreach (int i, string soldierName : soldierNames)
{
	int health = healthValues[i];
	if (health > 50)
	PrintFormat("%1: Healthy (%2%%)", soldierName, health);
}
