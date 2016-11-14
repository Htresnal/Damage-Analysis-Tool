Damage Analysis Tool v0.4
	Emulates fight process and logs out all the end information. You can choose time, customize sides(Attacker and Defender), apply effects, bonuses and etc.

Compiler: TDM-GCC-64
IDE: Code::Blocks 16.01
Plugins: wxWidgets 3.1.0

What is so special about this program?:
- Emulation is hit-based. That means, inbetween every hit, program calculates all the changes happened.
- 28 appliable effects: Critical hit, Manaburn, Feast, Backstab, Damage amplification, Double hit, Fury Swipes, Stat steal and etc.
- Damage done is split by 3 channels(Physical, Magical, Pure). Each with it's own reduce\amplification percentage.
- Damage is calculated as "Attacker does damage to Defender"(One way only).

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