Damage Analysis Tool
	Emulates fight, allows to get a total hit-wise information: total hits done, health and mana left, attack speed, raw damage and damage per hit and etc.
	
Compiler: MinGW32

Whats new about this programm:
- Emulation is hit-based. That means everytime hero makes a hit, program calculates all changes happened during time inbetween it and the previous hit.
- Easy update. By extracting npc_heroes.txt and dota_english.txt into the programm folder, you can stay up to date with hero data.
npc_heroes.txt could be found inside the *.gcf archive;
dota_english.txt is inside the game folder;
- There are total of 28 appliable effects: Critical hit, Manaburn, Feast, Backstab, Damage amplification, Double hit, Fury Swipes, Stat steal and etc.
- Damage done is split by 3 channels(Physical, Magical, Pure). Each with it's own reducement\amplification.
- Damage is calculated strictly by the formula "Defender <- Attacker"(One way only).

Changelog:
v0.1
- Initial release
v0.2
- Added 15 more applicable effects.
v0.3
- Fixed Base Attack Time crash when value is zero or less
- Starting Withstand field is now 10
- Fixed unneeded zeros appearing when changing Base Attack Time field.
- Lethal hit: Now also displays time.
- New effect: Bonus attack speed.
v0.4
- Cosmetic improvements.
- Fixed incorrect Game Settings data appearance.

Planned features:
- Mana cost calculating feature.

Updating game related files:
	dota_english.txt - This file can be found at: Steam\steamapps\common\dota 2 beta\game\dota\resource
	npc_heroes.txt - To obtain this file you need to access Steam\steamapps\common\dota 2 beta\game\dota\pak01_dir.vpk with GCFScape programm, and inside of it, at pak01_dir.vpk\scripts\npc you can find it.
