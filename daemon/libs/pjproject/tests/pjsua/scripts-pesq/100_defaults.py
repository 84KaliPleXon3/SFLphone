# $Id: 100_defaults.py 2063 2008-06-26 18:52:16Z nanang $
#
from inc_cfg import *

ADD_PARAM = ""

if (HAS_SND_DEV == 0):
	ADD_PARAM += "--null-audio"

# Call with default pjsua settings
test_param = TestParam(
		"PESQ defaults pjsua settings",
		[
			InstanceParam("UA1", ADD_PARAM + " --max-calls=1 --play-file wavs/input.16.wav"),
			InstanceParam("UA2", "--null-audio --max-calls=1 --rec-file  wavs/tmp.16.wav --clock-rate 16000 --auto-answer 200")
		]
		)

pesq_threshold = None
