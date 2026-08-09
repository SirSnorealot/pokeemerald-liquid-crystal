voice_group lc_intro_sfx
@ Voices for the GBC-ported LC sfx. Select with VOICE/program change in the midi.
@ GB envelopes: m4a attack/decay/release step ~= GB fade period (hardware caps at 7,
@ so GB fade 8 becomes 7). Initial GB volumes are carried by note velocity instead.
@ Square sweep byte = GB NR10: (time << 4) | (0x08 if pitch falls) | shift.

@ 000 Sfx_IntroUnown1/2: 50% duty, swell in (square_note 8, 3, -1), fade out (square_note 32, 14, 2)
	voice_square_1 60, 0, 0, 2, 1, 2, 0, 2
@ 001 Sfx_IntroUnown3: GB ch7 = wave channel; Crystal wave #2, NR32 volume carried by velocity
	voice_programmable_wave 60, 0, ProgrammableWaveData_LcWave2, 0, 7, 15, 0
@	voice_square_1 60, 0, 0, 0, 0, 2, 0, 2 @ old: misread ch7 as square
@ 002 Sfx_DittoPopUp drop: 50% duty, pitch_sweep 1, -6 (NR10 0x1E), fade 2
	voice_square_1 60, 0, 30, 2, 0, 2, 0, 1
@ 003 Sfx_DittoPopUp rise: 50% duty, pitch_sweep 1, 6 (NR10 0x16), fade 1
	voice_square_1 60, 0, 22, 2, 0, 1, 0, 1
@ 004 Sfx_DittoTransform swell: 25% duty, pitch_sweep 2, 6 (NR10 0x26), square_note 20, 3, -3
	voice_square_1 60, 0, 38, 1, 3, 0, 15, 2
@ 005 Sfx_DittoTransform tail: 25% duty, pitch_sweep 2, 6, fade 7 (last note's fade 2 lands on release)
	voice_square_1 60, 0, 38, 1, 0, 7, 0, 2
@ 006 Sfx_IntroPichu chirp down: 75% duty, pitch_sweep 4, -5 (NR10 0x4D), fade 8
	voice_square_1 60, 0, 77, 3, 0, 7, 0, 7
@ 007 Sfx_IntroPichu chirp up: 75% duty, pitch_sweep 1, 7 (NR10 0x17), fade 8
	voice_square_1 60, 0, 23, 3, 0, 7, 0, 7
@ 008 Sfx_DittoBounce impact: 50% duty, pitch_sweep 2, -4 (NR10 0x2C), fade 2 then 1
	voice_square_1 60, 0, 44, 2, 0, 2, 0, 1
@ 009 Sfx_DittoBounce rebound: 50% duty, pitch_sweep 3, 4 (NR10 0x34), fade 1
	voice_square_1 60, 0, 52, 2, 0, 1, 0, 1
@ 010 Sfx_GameFreakPresents arpeggio: 50% duty, pitch_sweep 15, -7 (time caps at 7 -> NR10 0x7F), note_type fade 1
	voice_square_1 60, 0, 127, 2, 0, 1, 0, 1
@ 011 Sfx_Tingle: 25% duty, note_type fade 1
	voice_square_1 60, 0, 0, 1, 0, 1, 0, 1
@ 012 Sfx_TwoPcBeeps / Sfx_4NoteDitty: 50% duty, fade 8 (near-sustained beeps)
	voice_square_1 60, 0, 0, 2, 0, 7, 0, 7
@ 013 Sfx_4NoteDitty final note: 50% duty, volume_envelope 4, 3 fade-out
	voice_square_1 60, 0, 0, 2, 0, 3, 0, 3
@ 014 Sfx_Twinkle: 12.5% duty, note_type fade 1
	voice_square_1 60, 0, 0, 0, 0, 1, 0, 1

@ Noise (GB ch8) voices; period = NR43 width bit (0 = 15-bit hiss, 1 = 7-bit buzz).
@ Noise pitch (NR43 divider) comes from the midi key, not the voice.
@ 015 Sfx_IntroSuicune1 open: 7-bit (noise 0x59), fade 8
	voice_noise_alt 60, 0, 1, 0, 7, 0, 7
@ 016 Sfx_IntroSuicune4 cracks: 7-bit (noise 0x5C/0x4D), fade 1
	voice_noise_alt 60, 0, 1, 0, 1, 0, 1
@ 017 Sfx_IntroSuicune1 tail / Suicune2 taps: 15-bit, fade 1
	voice_noise_alt 60, 0, 0, 0, 1, 0, 1
@ 018 Sfx_IntroSuicune2/4 body: 15-bit, fade 2
	voice_noise_alt 60, 0, 0, 0, 2, 0, 2
@ 019 Sfx_IntroSuicune2 fade-out: 15-bit, fade 3
	voice_noise_alt 60, 0, 0, 0, 3, 0, 3
@ 020 Sfx_IntroSuicune3 steps: 15-bit, fade 4
	voice_noise_alt 60, 0, 0, 0, 4, 0, 4
@ 021 Sfx_IntroSuicune3 open: 15-bit, fade 8
	voice_noise_alt 60, 0, 0, 0, 7, 0, 7
@ 022 Sfx_IntroSuicune3 rise: 15-bit swell (noise_note 8, 3, -1)
	voice_noise_alt 60, 0, 0, 1, 0, 15, 2
