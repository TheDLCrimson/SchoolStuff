import matplotlib.pyplot as plt
import matplotlib.patches as mpatches


blocks_first_fit = [
    {"size": 150, "status": "allocated"},
    {"size": 300, "status": "allocated"},
    {"size": 50, "status": "wasted"},
    {"size": 200, "status": "allocated"},
    {"size": 200, "status": "wasted"},
    {"size": 100, "status": "allocated"},
    {"size": 100, "status": "wasted"},
    {"size": 300, "status": "free"},
]

blocks_best_fit = [
    {"size": 150, "status": "allocated"},
    {"size": 100, "status": "allocated"},
    {"size": 250, "status": "wasted"},
    {"size": 400, "status": "allocated"},
    {"size": 200, "status": "allocated"},
    {"size": 300, "status": "allocated"},
]

blocks_worst_fit = [
    {"size": 150, "status": "free"},
    {"size": 200, "status": "allocated"},
    {"size": 150, "status": "wasted"},
    {"size": 300, "status": "allocated"},
    {"size": 100, "status": "wasted"},
    {"size": 100, "status": "allocated"},
    {"size": 100, "status": "wasted"},
    {"size": 150, "status": "allocated"},
    {"size": 150, "status": "wasted"},
]


def calculate_fragmentation(blocks):
    internal_frag = sum(block["size"] for block in blocks if block["status"] == "wasted")
    external_frag = sum(block["size"] for block in blocks if block["status"] == "free")
    total_wasted = internal_frag + external_frag
    return internal_frag, external_frag, total_wasted


def create_chart(blocks, title, ax, fragmentation):
    current_x = 0
    colors = {"free": "lightblue", "allocated": "orange", "wasted": "grey"}
    for block in blocks:
        ax.add_patch(
            mpatches.Rectangle(
                (current_x, 0), block["size"], 1, facecolor=colors[block["status"]], edgecolor="black"
            )
        )
        ax.text(
            current_x + block["size"] / 2, 0.5, f"{block['size']} KB", ha="center", va="center", fontsize=8
        )
        current_x += block["size"]
    ax.set_xlim(0, sum([block["size"] for block in blocks]))
    ax.set_ylim(0, 1)
    ax.axis("off")
    ax.set_title(title, fontsize=12)
    
    internal_frag, external_frag, total_wasted = fragmentation
    ax.text(
        sum([block["size"] for block in blocks]) / 2,
        -0.3,
        f"Internal: {internal_frag} KB, External: {external_frag} KB, Total Wasted: {total_wasted} KB",
        ha="center",
        va="center",
        fontsize=10,
        color="black",
    )


frag_first_fit = calculate_fragmentation(blocks_first_fit)
frag_best_fit = calculate_fragmentation(blocks_best_fit)
frag_worst_fit = calculate_fragmentation(blocks_worst_fit)


fig, axs = plt.subplots(3, 1, figsize=(12, 8))
create_chart(blocks_first_fit, "First Fit Strategy", axs[0], frag_first_fit)
create_chart(blocks_best_fit, "Best Fit Strategy", axs[1], frag_best_fit)
create_chart(blocks_worst_fit, "Worst Fit Strategy", axs[2], frag_worst_fit)


legend_labels = [
    mpatches.Patch(color="orange", label="Allocated Memory Space"),
    mpatches.Patch(color="lightblue", label="Free Memory Space"),
    mpatches.Patch(color="grey", label="Wasted Memory Space"),
]
fig.legend(handles=legend_labels, loc="upper center", bbox_to_anchor=(0.5, 0.97), ncol=3, fontsize=10)

plt.tight_layout(rect=[0, 0, 1, 0.95])
plt.show()
