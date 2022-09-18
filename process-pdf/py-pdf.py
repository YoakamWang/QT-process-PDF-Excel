import pandas as pd
import pdfplumber
import shutil
from pathlib import Path
import os
import sys

tags = []


def get_path():
    if len(sys.argv) < 2:
        print("Please try again")
        sys.exit()
    path = sys.argv[1]
    rel_path = os.path.split(path)
    basepath = rel_path[0]
    filename = rel_path[1]
    exe_name = os.path.splitext(filename)
    rel_filename = exe_name[0]
    return path, basepath, rel_filename


def extract_table_info():
    global tags
    filepath, basepath, real_filename = get_path()
    with pdfplumber.open(filepath) as pdf:
        for i in range(len(pdf.pages)):
            page = pdf.pages[i]
            #print(i)
            writer = pd.ExcelWriter(basepath + '/' + real_filename + "_page" + str(i) + ".xlsx", engine="openpyxl")
            tables_info = page.extract_tables()
            for index in range(len(tables_info)):
                # 设置表格的第一行为表头，其余为数据
                df_table = pd.DataFrame(tables_info[index][1:], columns=tables_info[index][0])
                df_table.to_excel(basepath + "/sheet" + str(index) + ".xlsx", index=False)
                tags.append(basepath + "/sheet" + str(index) + ".xlsx")
            # `print(tags)
            for tag_value in tags:
                data = pd.read_excel(tag_value, engine="openpyxl")
                data.to_excel(writer, os.path.splitext(os.path.split(tag_value)[1])[0], index=False)
            writer.save()
            writer.close()
            del_file()
            tags = []
            # time.sleep(5)


def del_file():
    for elme in tags:
        elm = Path(elme)
        elm.unlink() if elm.is_file() else shutil.rmtree(elm)


if __name__ == "__main__":
    extract_table_info()
    del_file()
    print("Process completed!")
