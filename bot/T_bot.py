import ctypes
from ctypes import *

lib = ctypes.CDLL('./templatematch_bot/T_bot_pyCall.so')

lib.newTBot.restype = c_void_p
# lib.call.argtypes = [c_void_p, c_void_p, c_void_p]

class T_bot:
    def __init__(self):
        self.T_bot_ptr = lib.newTBot()
    def speak(self, s):
        instr = bytes(s)
        outstr = bytes(100)
        lib.call(self.T_bot_ptr, instr, outstr)
        answer = outstr.decode()
        return answer