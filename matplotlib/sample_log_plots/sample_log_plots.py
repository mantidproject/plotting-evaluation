import mantid
from mantid.simpleapi import Load

import datetime as dt
import matplotlib.pyplot as plt
import numpy as np

ISO_TIMESTAMP_FORMAT = '%Y-%m-%dT%H:%M:%S'
MTD_TIMESTAMP_FORMAT = '%Y-%m-%d %H:%M:%S'

# ----------------------------------------------------------------------------------------------------------------------

def to_datetime_iso(mtd_dt):
    return dt.datetime.strptime(str(mtd_dt).strip(), ISO_TIMESTAMP_FORMAT)

# ----------------------------------------------------------------------------------------------------------------------

def is_running(ts, run_start, running_times, running_values):
    print "ts={}, run_start={}".format(ts, run_start)
    if ts < run_start:
        return False
    print "t0={}, t(-1)={}".format(running_times[0], running_times[-1])
    if ts < running_times[0] or ts > running_times[-1]:
        return False
    running = True
    for i in range(len(running_times) - 1):
        print "ts={}, rt(i)={}, rt(i+1)={}".format(ts,  running_times[i], running_times[i+1])
        if (ts >= running_times[i]) and (ts < running_times[i+1]):
            running = running_values[i]
            print "found ",i, running
            break
    return running

# ----------------------------------------------------------------------------------------------------------------------


w = Load('/mnt/data1/source/github/mantidproject/mantid/builds/debug/ExternalData/Testing/Data/SystemTest/LARMOR/LARMOR00000063.nxs')
r = w.run()
run_start = dt.datetime.strptime(str(r.startTime()).strip(), ISO_TIMESTAMP_FORMAT)

dae_beam_current = r.getLogData('dae_beam_current')
# running log is series of boolean values indicating run status
running_log = w.run().getLogData('running')
running_times = []
for t in running_log.times:
    running_times.append(to_datetime_iso(t))

# create times as offset from run_start
uamps_times, uamps_values = dae_beam_current.times, dae_beam_current.value
delta_t, uamps_datetime = [], []
for t in uamps_times:
    t1, t2 = run_start, to_datetime_iso(t)
    uamps_datetime.append(t2)
    if t2 < t1:
        delta_t.append(-(t1-t2).seconds)
    else:
        delta_t.append((t2-t1).seconds)

# is it considered running?
is_not_running = np.full_like(uamps_values, True)
for index, utime in enumerate(uamps_times):
    t = to_datetime_iso(utime)
    is_not_running[index] = not is_running(t, run_start, running_times, running_log.value)

print running_log.times
print running_log.value
print uamps_times
print is_not_running
print delta_t

delta_t = np.array(delta_t, dtype='float64')
plt.plot(delta_t, uamps_values)
plt.fill_between(delta_t, uamps_values[0], uamps_values[-1], alpha=0.3, facecolor='grey')
plt.show()
