
def safe_compare(value1, value2):
    """
    比较两个值，如果是字符串，自动处理编码问题，如果是其他类型，直接必须要求类型一致，并比较值
    """
    if isinstance(value1, unicode) and isinstance(value2, str):
        return value1 == value2.decode('utf-8')
    elif isinstance(value1, str) and isinstance(value2, unicode):
        return value1.decode('utf-8') == value2
    else:
        return type(value1) == type(value2) and value1 == value2

def generate_diff(old, new, exclude_keys=()):
    """
    深度比较两个结构
    :param exclude_keys: set/list/tuple，表示需排除dict中的key名。

    返回差异：
    - 若完全相同，返回 {}
    - 若不同，返回 { ...diff... } or [{ ...diff... }, ...]

    diff 说明：
        !: 表示有变化, 其中,- 表示旧值, + 表示新的值
        +: 表示新增
        -: 表示删除

    Examples:

        >>> generate_diff(1, 2)
        {'!': {'+': 2, '-': 1}}

        >>> generate_diff(1, 1)
        {}

        >>> generate_diff("123", "1234")
        {'!': {'+': '1234', '-': '123'}}

        >>> generate_diff(False, True)
        {'!': {'+': True, '-': False}}

        >>> generate_diff([1,2,4], [1,2,3,4,5])
        {
            "2": {
                "!": {
                    "-": 4,
                    "+": 3
                }
            },
            "3": {
                "+": 4
            },
            "4": {
                "+": 5
            }
        }

        >>> old_conf = {
                "key": "req_body",
                "operation": "include",
                "type": "string",
                "value": "\"jsonrpc\""
            }
        >>> new_conf = {
                "key": "req_body",
                "operation": "regular_exp",
                "type": "string",
                "value": '"method"\s*:\s*"(initialize|notifications/initialized|tools/[^/]+|resources(?:/templates)?/[^/]+|prompts/[^/]+)"'
            }
        >>> generate_diff(old_conf, new_conf)
        [
            {
                "!": {
                    "value": {
                        "!": {
                        "-": "\\"jsonrpc\\"",
                        "+": "\\"method\\"\\s*:\\s*\\"(initialize|notifications/initialized|tools/[^/]+|resources(?:/templates)?/[^/]+|prompts/[^/]+)\\""
                        }
                    }
                }
            },
            {
                "!": {
                    "operation": {
                        "!": {
                        "-": "include",
                        "+": "regular_exp"
                        }
                    }
                }
            }
        ]
    """
    if not isinstance(exclude_keys, (tuple, list, set)):
        exclude_keys = () # 如果不元组，列表，集合时，不生效
    exclude_keys = set(exclude_keys)

    # 基础类型（str/int/bool/None）
    if not isinstance(old, (dict, list)):
        if not safe_compare(old, new):
            return {"!": {"-": old, "+": new}}
        return {}

    # 字典比较
    if isinstance(old, dict):
        diffs = []
        all_keys = set(old.keys()) | set(new.keys())
        for key in all_keys:

            if key in exclude_keys:
                continue
            if key not in old and key in new:
                diffs.append({"+": {key: new[key]}}) 
                continue
            if key not in new and key in old:
                diffs.append({"-": {key: old[key]}})
                continue

            o = old.get(key)
            n = new.get(key)
            sub = generate_diff(o, n, exclude_keys=exclude_keys)
            if sub:  # 有差异才记录
                if type(sub) == list:
                    diffs.append({"!": {key: sub}})
                else:
                    op = sub.get("-", None) or sub.get("+", None) or "!"
                    diffs.append({op: {key: sub}})
        return diffs if diffs else {}

    # 列表比较
    if isinstance(old, list):
        diff = {}

        max_len = max(len(old), len(new))
        for i in range(max_len):
            if i >= len(old) and i < len(new):
                diff[i] = {"+": new[i]}
                continue
            if i >= len(new) and i < len(old):
                diff[i] = {"-": old[i]}
                continue
            o = old[i] 
            n = new[i] 
            sub = generate_diff(o, n, exclude_keys=exclude_keys)
            if sub:
                diff[i] = sub
        return diff if diff else {}

    return {}
