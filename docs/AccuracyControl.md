[Back to **Limb Darkening**](LimbDarkening.md)

# Accuracy control

The accuracy goal of the calculation can be controlled by the user through the property ```VBBL.Tol```. In fact, ```ESPLMag2``` and ```BinaryMag2``` refine their calculations until they match the required accuracy goal. The result will be ```Mag``` $\pm$ ```VBBL.Tol``` (absolute accuracy).

Keep in mind that the computational time typically scales as ```VBBL.Tol^(-1/2)```. By default ```VBBL.Tol``` is set to ```1.e-2```.

Here are some examples:

```
double Mag, s, q, y1, y2;
s = 0.8;
q = 0.1;
y1 = 0.01;
y2 = 0.01;

VBBL.Tol = 1.e-3; 
Mag = VBBL.BinaryMag2(s, q, y1, y2, Rs); 
printf("Magnification (accuracy at 1.e-3) = %lf\n", Mag); // Output should be 18.283....

VBBL.Tol = 1.e-4;
Mag = VBBL.BinaryMag2(s, q, y1, y2, Rs);
printf("Magnification (accuracy at 1.e-4) = %lf\n", Mag); // Output should be 18.2833....
```

## Precision control

In general, the photometric precision of ground observatories is around 0.001. Therefore, it makes sense to set a relative precision goal, instead of an asbolute accuracy goal. This is set by ```VBBL.RelTol```. The result will be ```Mag```$\pm$ ```Mag*VBBL.RelTol``` (relative precision).

For example, let us set a poor 10% precision, just to see the difference:

```
VBBL.RelTol = 1.e-1;
Mag = VBBL.BinaryMag2(s, q, y1, y2, Rs); 
printf("Magnification (relative precision at 1.e-1) = %lf\n", Mag); // Output should be 18.24.... (matching the required precision)
```

If you do not want to use relative precision, just set ```VBBL.RelTol = 0;``` which is the default value.

In general, the calculation stops when the first of the two goals is reached, either absolute accuracy or relative precision.
