
# Advanced controls

The functions ```ESPLMag2``` and ```BinaryMag2``` are designed 

	// After each calculation, the number of annuli used is available in VBBL.nannuli.
	// If you are probing extremely tiny caustics with very large sources, you may impose a minimum number of annuli.
	// Before your calculation, just set
	// VBBL.minannuli=2; //or whatever you need 
	// The total number of points used is available in VBBL.NPS
	printf("Annuli used: %d\nTotal number of points: %d\n", VBBL.nannuli, VBBL.NPS);
  
