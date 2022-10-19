#
# Copyright (C) 2022, b40yd
#
# Author: b40yd <bb.qnyd@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

from typing import Dict, List
from urllib import parse


def urls() -> List:
    return [
        "/api/v1/test",
        "/api/v1/test/1",
        "/api/v1/test/2",
        "/api/v1/test/3",
        "/api/v1/test/4",
        "/api/v1/t1/1/2",
        "/api/v1/t1/3/1",
        "/api/v1/t1/3/2",
        "/api/v1/t1/2/2",
        "/api/v1/customer/12/order/1",
        "/api/v1/customer/12/order/2",
        "/api/v1/customer/12/order/3",
        "/api/v1/customer/12/order/4",
        "/api/v1/customer/12/order/5",
        "/api/v1/customer/1/order/12",
        "/api/v1/customer/11/order/112",
        "/api/v1/customer/10/order/1122",
        "/api/v1/customer/112/order/1232",
        "/api/v1/maziwang/article/1",
        "/api/v1/maziwu/article/1",
        "/api/v1/maziliu/article/1",
        "/api/v1/mazizhang/article/1",
        "/api/v1/mazili/article/1",
        "/api/v1/wangzi/blog/xss",
        "/api/v1/wangzi/blog/sqli",
        "/api/v1/wangzi/blog/javascript",
        "/api/v1/wanger/blog/xss",
        "/api/v1/wanger/blog/sqli",
        "/api/v1/wanger/blog/javascript",
    ]


def normal_number(path) -> str:
    for i, p in enumerate(path):
        if p.isdigit():
            path[i] = "{" + "n{}".format(i) + "}"
    return path


def normal_str(paths):
    """
    Automatically identify standardized template parameters and identify dynamic parameters according to subpaths
    """
    all_paths = set()
    if len(paths) == 1:
        all_paths.update(paths)
    for i, p in enumerate(paths):
        if i >= len(paths):
            all_paths.add("/" + p)
            break
        mark = {}
        for p1 in list(paths)[i + 1:]:
            path = str(p).strip("/").split("/")
            result = diff_path(path, str(p1).strip("/").split("/"))
            # mark["{}".format(i1 + 1)] = result
            flag = False
            position = result.split("_")
            if len(position) > 3:
                for i in position:
                    if ((int(i) + 1) == int(position[int(i) + 1])
                            and (int(i) + 2) == int(position[int(i) + 2])
                            and (int(i) + 3) == int(position[int(i) + 3])):
                        flag = True
                        break
            elif len(position) == 3:
                if (int(position[0]) + 1) == int(
                        position[1]) and (int(position[0]) + 2) == int(
                            position[2]):
                    flag = True
            # elif "{" in p:
            #     all_paths.add(p)
            if flag:
                continue
            mark[result] = path

        # print(i, "----", mark)
        for k, v in mark.items():
            position = k.split("_")
            for pos in position:
                # print(k, "====", position, "----", pos, v)
                if pos == "" or "{" in v[int(pos)]:
                    continue
                else:
                    v[int(pos)] = "{c%s}" % pos
            tmp_url = "/" + "/".join(v)
            all_paths.add(tmp_url)
    return all_paths


def diff_path(p1, p2):
    mark = [0 for _ in p1]
    result = ""
    for i, p in enumerate(p1):
        if p == p2[i]:
            mark[i] = 1

    for i, m in enumerate(mark):
        if m == 0:
            result += str(i) + "_"
    return result.strip("_")


def split_path() -> Dict:
    """
    Automatically identify standardized template parameters, if the path is a number, it represents a dynamic parameter, and deduplication
    """
    table = {}
    for url in urls():
        path_arr = url.strip("/").split("/")
        path_arr = normal_number(path_arr)
        # print(path_arr)
        val = table.get(len(path_arr), None)

        if type(val) is set:
            val.add("/" + "/".join(path_arr))
            continue
        table[len(path_arr)] = set(["/" + "/".join(path_arr)])
    return table


def main():
    path = parse.urlsplit("http://www.example.com:80/a/b/c?id=1&n=hello")
    tree = {path.hostname: {path.port: []}}
    # print(tree, "===")
    tree = split_path()
    # print(tree, "....")
    all_result = set()
    for _, paths in tree.items():
        # print(index, paths)
        mark = normal_str(paths)
        # print(mark, "=====")
        all_result.update(mark)
    print(all_result)


if __name__ == "__main__":
    main()
