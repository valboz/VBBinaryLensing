import numpy as np
import VBBinaryLensing
import os
from functools import partial

### Tests as instructions

VBB = VBBinaryLensing.VBBinaryLensing()
VBB.LoadESPLTable(os.path.dirname(VBBinaryLensing.__file__)+'/VBBinaryLensing/data/ESPL.tbl')


    
def test_all():

    # Quick start
    s = 0.8
    q = 0.1
    y1 = 0.01
    y2 = 0.01
    Rs = 0.01

    Mag = VBB.BinaryMag2(s, q, y1, y2, Rs)
    assert np.allclose(Mag,18.28,atol = 0.01)

    # Accuracy control
    VBB.Tol = 1.e-3
    Mag = VBB.BinaryMag2(s, q, y1, y2, Rs)
    assert np.allclose(Mag,18.283,atol = 0.001)

    VBB.Tol = 1.e-4
    Mag = VBB.BinaryMag2(s, q, y1, y2, Rs)
    assert np.allclose(Mag,18.2833,atol = 0.0001)

    VBB.Tol = 1.e-2

    VBB.RelTol = 1.e-1
    Mag = VBB.BinaryMag2(s, q, y1, y2, Rs)
    assert np.allclose(Mag,18.36,atol = 0.01)

    VBB.RelTol = 0

    # Astrometry

    VBB.astrometry = True
    Mag = VBB.BinaryMag2(s, q, y1, y2, Rs)
    assert np.allclose(VBB.astrox1 - y1,-0.1645,atol = 0.0001)
    assert np.allclose(VBB.astrox2 - y2,-0.0743,atol = 0.0001)
    VBB.astrometry = False

    # Limb darkening

    VBB.a1 = 0.51
    Mag = VBB.BinaryMag2(s, q, y1, y2, Rs)
    assert np.allclose(Mag,18.27,atol = 0.01)
    VBB.a1 = 0.0

    # Limb darkening with arbitray profiles

    VBB.Tol = 1.e-4
    VBB.SetLDprofile(VBB.LDsquareroot)
    VBB.a1 = 0.51
    VBB.a2 = 0.3
    Mag = VBB.BinaryMag2(s, q, y1, y2, Rs)
    assert np.allclose(Mag,18.2712,atol = 0.0001)


    VBB.SetLDprofile(VBB.LDquadratic)
    VBB.a1 = 0.51
    VBB.a2 = 0.3
    Mag = VBB.BinaryMag2(s, q, y1, y2, Rs)
    assert np.allclose(Mag,18.2709,atol = 0.0001)


    VBB.SetLDprofile(VBB.LDlog)
    VBB.a1 = 0.51
    VBB.a2 = 0.3
    Mag = VBB.BinaryMag2(s, q, y1, y2, Rs)
    assert np.allclose(Mag,18.2779,atol = 0.0001)



    VBB.Tol = 1.e-2
    Mag = VBB.BinaryMag0(s, q, y1, y2)
    assert np.allclose(Mag,18.18,atol = 0.01)

    u = 0.1
    Mag = VBB.ESPLMag2(u, Rs)
    assert np.allclose(Mag,10.05,atol = 0.01)


