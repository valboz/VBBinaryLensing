import numpy as np
import VBBinaryLensing

VBBL = VBBinaryLensing.VBBinaryLensing()

def test_ESPL_magnification():
    u = 1.
    rho = 0. 
    VBBL.LoadESPLTable("../data/ESPL.tbl")
    magnification = VBBL.ESPLMag2(u, rho)

    assert np.allclose(magnification, 3./np.sqrt(5.))

#def test_amplification_USBL():
#    s = 1.
#    q = 0.02
#    y1 = 0.5 
#    y2 = 0.5 
#    rho = 0.0033
#    VBBL.Tol = 1.e-3
#
#    magnification = VBBL.BinaryMag2(s, q, y1, y2, rho);
#
#    # Reset Tol
#    VBBL.Tol = 0.01
#
#    assert np.allclose(magnification, 1.6311724868)
#
def test_amplification_PSBL():
    s = 1.
    q = 0.02
    y1 = 0.5
    y2 = 0.5 

    magnification = VBBL.BinaryMag0(s, q, y1, y2);

    assert np.allclose(magnification, 1.63109244)
