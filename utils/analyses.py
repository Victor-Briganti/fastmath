import pandas as pd
import matplotlib.pyplot as plt
import os
import glob
import numpy as np


def plot_results(df_results, output_dir):
    fig, (ax1, ax3) = plt.subplots(2, 1, figsize=(12, 12))

    x = np.arange(len(df_results["function"]))
    ax1.bar(
        x,
        df_results["speedup"],
        color="skyblue",
        alpha=0.7,
        label="Speedup",
    )
    ax1.set_ylabel("Speedup", color="black")
    ax1.tick_params(axis="y", labelcolor="black")
    ax1.set_xticks(x)
    ax1.set_xticklabels(df_results["function"], rotation=45)
    ax1.set_title("Speedup vs Absolute Error")
    ax1.grid(axis="y", linestyle="--", alpha=0.7)

    ax2 = ax1.twinx()
    ax2.plot(
        x, df_results["max_abs_err"], color="red", marker="o", label="Max Abs Error"
    )
    ax2.plot(
        x,
        df_results["avg_abs_err"],
        color="darkred",
        marker="x",
        linestyle="--",
        label="Avg Abs Error",
    )
    ax2.set_ylabel("Absolute Error", color="black")
    ax2.set_yscale("log")
    ax2.tick_params(axis="y", labelcolor="black")

    lines1, labels1 = ax1.get_legend_handles_labels()
    lines2, labels2 = ax2.get_legend_handles_labels()
    ax2.legend(lines1 + lines2, labels1 + labels2, loc="upper left")

    ax3.bar(
        x,
        df_results["speedup"],
        color="lightgreen",
        alpha=0.7,
        label="Speedup (x)",
    )
    ax3.set_ylabel("Speedup (x)", color="black")
    ax3.tick_params(axis="y", labelcolor="black")
    ax3.set_xticks(x)
    ax3.set_xticklabels(df_results["function"], rotation=45)
    ax3.set_title("Speedup vs Relative Error (%)")
    ax3.grid(axis="y", linestyle="--", alpha=0.7)

    ax4 = ax3.twinx()
    ax4.plot(
        x,
        df_results["max_rel_err_pct"],
        color="purple",
        marker="o",
        label="Max Rel Error (%)",
    )
    ax4.plot(
        x,
        df_results["avg_rel_err_pct"],
        color="indigo",
        marker="x",
        linestyle="--",
        label="Avg Rel Error (%)",
    )
    ax4.set_ylabel("Relative Error (%)", color="black")
    ax4.set_yscale("log")
    ax4.tick_params(axis="y", labelcolor="black")

    lines3, labels3 = ax3.get_legend_handles_labels()
    lines4, labels4 = ax4.get_legend_handles_labels()
    ax4.legend(lines3 + lines4, labels3 + labels4, loc="upper left")

    plt.tight_layout()
    plot_file = os.path.join(output_dir, "analysis_plots.png")
    plt.savefig(plot_file)
    print(f"Analysis plots saved to {plot_file}")


def load_results(output_dir):
    results = []
    speed_files = glob.glob(os.path.join(output_dir, "*_speed.csv"))

    for speed_file in speed_files:
        func_name = os.path.basename(speed_file).replace("_speed.csv", "")
        error_file = os.path.join(output_dir, f"{func_name}_error.csv")

        if not os.path.exists(error_file):
            print(f"Warning: Error file for {func_name} not found. Skipping.")
            continue

        df_speed = pd.read_csv(speed_file)
        avg_common_speed = df_speed["common"].mean()
        avg_fast_speed = df_speed["fast"].mean()

        speedup = avg_common_speed / avg_fast_speed if avg_fast_speed > 0 else 0

        df_error = pd.read_csv(error_file)
        df_error = df_error.replace([np.inf, -np.inf], np.nan).dropna(
            subset=["abs_err", "rel_err"]
        )

        if df_error.empty:
            print(f"Warning: No valid error data for {func_name}. Skipping.")
            continue

        max_abs_err = df_error["abs_err"].max()
        avg_abs_err = df_error["abs_err"].mean()
        max_rel_err_pct = df_error["rel_err"].max() * 100
        avg_rel_err_pct = df_error["rel_err"].mean() * 100

        results.append(
            {
                "function": func_name,
                "avg_common_speed": avg_common_speed,
                "avg_fast_speed": avg_fast_speed,
                "speedup": speedup,
                "max_abs_err": max_abs_err,
                "avg_abs_err": avg_abs_err,
                "max_rel_err_pct": max_rel_err_pct,
                "avg_rel_err_pct": avg_rel_err_pct,
            }
        )

    if not results:
        return pd.DataFrame()

    df_results = pd.DataFrame(results)
    df_results.sort_values("function", inplace=True)
    return df_results


def main():
    output_dir = "output"
    df_results = load_results(output_dir)

    if df_results.empty:
        print("No results found.")
        return

    results_csv = os.path.join(output_dir, "results.csv")
    df_results.to_csv(results_csv, index=False)
    print(f"Summarized results saved to {results_csv}")
    plot_results(df_results, output_dir)


if __name__ == "__main__":
    main()
