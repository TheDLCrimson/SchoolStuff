import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

# Data for Gantt Chart
algorithms = [
    "FCFS Scheduling",
    "SJF Scheduling",
    "Non-Preemptive Priority Scheduling",
    "Round Robin Scheduling (Quantum=2)"
]

processes = [
    [("P1", 0, 2), ("P2", 2, 1), ("P3", 3, 8), ("P4", 11, 4), ("P5", 15, 5)],  # FCFS
    [("P2", 0, 1), ("P1", 1, 2), ("P4", 3, 4), ("P5", 7, 5), ("P3", 12, 8)],  # SJF
    [("P3", 0, 8), ("P5", 8, 5), ("P4", 13, 4), ("P1", 17, 2), ("P2", 19, 1)],  # Priority
    [("P1", 0, 2), ("P2", 2, 1), ("P3", 3, 2), ("P4", 5, 2), ("P5", 7, 2), ("P3", 9, 2), ("P4", 11, 2), ("P5", 13, 2), ("P3", 15, 2), ("P5", 17, 1), ("P3", 18, 3)],  # Round Robin
]

# Define colors for each process
colors = {
    "P1": "#1f77b4",
    "P2": "#ff7f0e",
    "P3": "#2ca02c",
    "P4": "#d62728",
    "P5": "#9467bd"
}

# Plotting the Gantt Chart
fig, ax = plt.subplots(figsize=(10, 6))
y_offset = 0
bar_height = 0.4

for idx, algorithm in enumerate(algorithms):
    y_offset = idx * 1.5  # Spacing between bars for different algorithms
    for task in processes[idx]:
        process_name, start_time, duration = task
        ax.barh(y_offset, duration, left=start_time, height=bar_height, color=colors[process_name], align='center', edgecolor='black', label=process_name if start_time == 0 else "")
    ax.text(20.5, y_offset, algorithm, va='center', fontsize=10, color='black')

# Create custom legend
handles = [mpatches.Patch(color=color, label=process) for process, color in colors.items()]
ax.legend(handles=handles, loc='upper left', ncol=5, title="Processes")

ax.set_xlabel("Time (ms)")
ax.set_yticks([])
ax.set_xlim(0, 20)
ax.grid(True, axis='x', linestyle='--', alpha=0.5)
plt.title("Gantt Chart for Scheduling Algorithms")
plt.tight_layout()
plt.show()