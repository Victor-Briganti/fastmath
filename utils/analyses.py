import os

import duckdb
import matplotlib.pyplot as plt
import numpy as np


# Generate both the speed and the error graph
def generate_graphs(df_speed, df_error, title, filename):
    colors = ["indigo", "gold"]
    speed_plot_data = (
        df_speed.groupby("function")[["common", "fast"]].mean().sort_index()
    )

    fig, ax = plt.subplots(figsize=(14, 12))

    speed_plot_data.plot(
        kind="bar",
        ax=ax,
        color=colors,
    )
    ax.set_title(f"{title} - Average Speed")
    ax.set_ylabel("Average Speed")
    ax.set_xlabel("Function Name")
    ax.tick_params(axis="x", rotation=45)

    plt.tight_layout()

    speed_file = os.path.join("report", f"{filename}_speed.pdf")
    plt.savefig(speed_file, format="pdf", bbox_inches="tight")
    plt.close(fig)

    # Clean infinite values and <= 0 for log scale
    df_error = df_error.replace([np.inf, -np.inf], np.nan).dropna(subset=["relative"])
    df_error = df_error[df_error["relative"] > 0]
    # Cap the maximum value to avoid matplotlib computing 10^300 and overflowing
    df_error["relative"] = df_error["relative"].clip(upper=1e100)

    if not df_error.empty:
        fig, ax = plt.subplots(figsize=(12, 6))

        error_plot_data = df_error.groupby("function")[["relative"]].mean()

        # Matplotlib bar plots on a log scale need a positive bottom, otherwise it raises an overflow warning
        min_val = error_plot_data["relative"].min()
        safe_bottom = min_val * 0.5 if min_val > 0 else 1e-10

        error_plot_data.plot(kind="bar", ax=ax, color=["red"], bottom=safe_bottom)

        ax.set_title(f"{title} - Relative Error")
        ax.set_ylabel("Relative Error")
        ax.set_xlabel("Function Name")
        ax.set_yscale("log")
        ax.tick_params(axis="x", rotation=45)
        plt.tight_layout()

        error_file = os.path.join("report", f"{filename}_error.pdf")
        plt.savefig(error_file, format="pdf", bbox_inches="tight")
        plt.close(fig)


def main():
    con = duckdb.connect(database=":memory:")
    os.makedirs("report", exist_ok=True)

    try:
        con.execute(
            "CREATE TABLE ErrorMath AS SELECT * FROM read_csv('output/error.csv', auto_detect=True);"
        )
        con.execute(
            "CREATE TABLE SpeedMath AS SELECT * FROM read_csv('output/speed.csv', auto_detect=True);"
        )
    except Exception as e:
        print(f"Error reading CSV files. Details: {e}")
        return

    query_speed = """
        SELECT 
            function, 
            precision, 
            version,
            AVG(common) AS common, 
            AVG(fast) AS fast 
        FROM SpeedMath 
        GROUP BY function, precision, version
    """
    query_error = """
        SELECT 
            function, 
            precision, 
            version,
            AVG(relative) AS relative 
        FROM ErrorMath 
        GROUP BY function, precision, version
    """

    df_speed = con.execute(query_speed).fetchdf()
    df_error = con.execute(query_error).fetchdf()

    generate_graphs(df_speed, df_error, "All Data", "aggregate")

    generate_graphs(
        df_speed[df_speed["version"] == "fast"],
        df_error[df_error["version"] == "fast"],
        "Fast Version",
        "fast",
    )
    generate_graphs(
        df_speed[(df_speed["version"] == "fast") & (df_speed["precision"] == "float")],
        df_error[(df_error["version"] == "fast") & (df_error["precision"] == "float")],
        "Fast Version (Float)",
        "fast_float",
    )
    generate_graphs(
        df_speed[(df_speed["version"] == "fast") & (df_speed["precision"] == "double")],
        df_error[(df_error["version"] == "fast") & (df_error["precision"] == "double")],
        "Fast Version (Double)",
        "fast_double",
    )
    generate_graphs(
        df_speed[df_speed["version"] == "common"],
        df_error[df_error["version"] == "common"],
        "Common Version",
        "common",
    )
    generate_graphs(
        df_speed[
            (df_speed["version"] == "common") & (df_speed["precision"] == "float")
        ],
        df_error[
            (df_error["version"] == "common") & (df_error["precision"] == "float")
        ],
        "Common Version (Float)",
        "common_float",
    )
    generate_graphs(
        df_speed[
            (df_speed["version"] == "common") & (df_speed["precision"] == "double")
        ],
        df_error[
            (df_error["version"] == "common") & (df_error["precision"] == "double")
        ],
        "Common Version (Double)",
        "common_double",
    )

    print("All graphs generated successfully on 'report' directory.")


if __name__ == "__main__":
    main()
