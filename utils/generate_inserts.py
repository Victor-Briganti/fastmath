import os
import csv

OUTPUT_DIR = "output"


def format_value(val):
    if val.lower() in ("inf", "+inf", "infinity"):
        return "'Infinity'"
    elif val.lower() in ("-inf", "-infinity"):
        return "'-Infinity'"
    elif val.lower() in ("nan", "-nan"):
        return "'NaN'"
    else:
        return val


with (
    open(os.path.join(OUTPUT_DIR, "error.csv"), "w", newline="") as error_csv,
    open(os.path.join(OUTPUT_DIR, "speed.csv"), "w", newline="") as speed_csv,
):
    error_writer = csv.writer(error_csv)
    speed_writer = csv.writer(speed_csv)
    error_writer.writerow(
        [
            "function",
            "x",
            "y",
            "common",
            "fast",
            "absolute",
            "relative",
            "precision",
            "version",
        ]
    )
    speed_writer.writerow(["function", "common", "fast", "precision", "version"])

    for version in os.listdir(OUTPUT_DIR):
        version_dir = os.path.join(OUTPUT_DIR, version)
        if not os.path.isdir(version_dir):
            continue

        for table_type in os.listdir(version_dir):
            type_dir = os.path.join(version_dir, table_type)
            if not os.path.isdir(type_dir):
                continue

            for precision in os.listdir(type_dir):
                prec_dir = os.path.join(type_dir, precision)
                if not os.path.isdir(prec_dir):
                    continue

                for file in sorted(os.listdir(prec_dir)):
                    if not file.endswith(".csv"):
                        continue

                    function_name = file[:-4]
                    file_path = os.path.join(prec_dir, file)

                    with open(file_path, "r") as csv_file:
                        reader = csv.reader(csv_file)
                        headers = next(reader)

                        if table_type == "error":
                            for row in reader:
                                if len(row) == 5:  # x, common, fast, abs_err, rel_err
                                    x, common, fast, abs_err, rel_err = [
                                        format_value(v) for v in row
                                    ]
                                    y = "NULL"
                                elif (
                                    len(row) == 6
                                ):  # a, b, common, fast, abs_err, rel_err
                                    x, y, common, fast, abs_err, rel_err = [
                                        format_value(v) for v in row
                                    ]
                                else:
                                    continue

                                error_writer.writerow(
                                    [
                                        function_name,
                                        x,
                                        y,
                                        common,
                                        fast,
                                        abs_err,
                                        rel_err,
                                        precision,
                                        version,
                                    ]
                                )

                        elif table_type == "speed":
                            for row in reader:
                                if len(row) == 2:
                                    common, fast = [format_value(v) for v in row]
                                    speed_writer.writerow(
                                        [
                                            function_name,
                                            common,
                                            fast,
                                            precision,
                                            version,
                                        ]
                                    )

print(
    f"CSV files generated at {os.path.join(OUTPUT_DIR, 'error.csv')} and {os.path.join(OUTPUT_DIR, 'speed.csv')}"
)
