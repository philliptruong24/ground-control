import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('data/clean_telemetry.csv')

fig, (ax1, ax2) = plt.subplots(nrows=2, ncols=1, figsize=(10, 8))

ax1.plot(df['timestamp_ms'], df['pitch_deg'], label='Pitch')
ax1.plot(df['timestamp_ms'], df['roll_deg'], label='Roll')
ax1.set_title('Drone Pitch and Roll')
ax1.set_xlabel('Time (ms)')
ax1.set_xlim(0, 20000)
ax1.set_ylabel('Angle (Degrees)')
ax1.legend()
ax1.grid(True)

ax2.plot(df['timestamp_ms'], df['yaw_deg'], label='Yaw', color='green')
ax2.set_title('Drone Yaw')
ax2.set_xlabel('Time (ms)')
ax2.set_xlim(0, 20000)
ax2.set_ylabel('Angle (Degrees)')
ax2.legend(loc='lower left')
ax2.grid(True)

plt.tight_layout()

plt.savefig('data/full_degree_plot.png')
print("Successfully rendered and saved subplots.")