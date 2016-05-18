Damage Analysis Tool
	Emulates fight, allows to get a total hit-wise information: total hits done, health and mana left, attack speed, raw damage and damage per hit and etc.

Whats new about this programm:
- Emulation is hit-based. That means everytime hero makes a hit, program calculates all changes happened during time inbetween it and the previous hit.
- Easy update. By extracting npc_heroes.txt and dota_english.txt into the programm folder, you can stay up to date with hero data.
npc_heroes.txt could be found inside the *.gcf archive;
dota_english.txt is inside the game folder;
- There are total of 28 appliable effects: Critical hit, Manaburn, Feast, Backstab, Damage amplification, Double hit, Fury Swipes, Stat steal and etc.
- Damage done is split by 3 channels(Physical, Magical, Pure). Each with it's own reducement\amplification.
- Damage is calculated strictly by the formula "Defender <- Attacker"(One way only).