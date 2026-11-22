import os, sys, errno, getopt, stat, shutil

def print_columns(items):
    if not items:
        return
    term_width = shutil.get_terminal_size(fallback=(80, 24)).columns
    max_len = max(len(item) for item in items) + 2
    cols = max(1, term_width // max_len)
    rows = (len(items) + cols - 1) // cols

    for r in range(rows):
        line_parts = []
        for c in range(cols):
            idx = r + c * rows
            if idx < len(items):
                if c == cols - 1 or idx + rows >= len(items):
                    line_parts.append(items[idx])
                else:
                    line_parts.append(items[idx].ljust(max_len))
        print("".join(line_parts))

def list_directory(dir_path, opts, show_header=False):
    try:
        dir_st = os.stat(dir_path)
        if not stat.S_ISDIR(dir_st.st_mode):
            print(f"ls: '{dir_path}': Not a directory", file=sys.stderr)
            return False
    except OSError as e:
        print(f"ls: cannot access '{dir_path}': {os.strerror(e.errno)}", file=sys.stderr)
        return False

    if show_header:
        print(f"{dir_path}:")

    names = []
    try:
        with os.scandir(dir_path) as it:
            for entry in it:
                if entry.name.startswith('.'):
                    continue
                names.append(entry.name)
    except OSError as e:
        print(f"ls: cannot open directory '{dir_path}': {os.strerror(e.errno)}", file=sys.stderr)
        return False

    names.sort(key=lambda s: (s.lower(), s))
    if opts['reverse']:
        names.reverse()

    sub_dirs = []
    if opts['recursive']:
        for name in names:
            full_path = os.path.join(dir_path, name)
            try:
                st = os.lstat(full_path)
                if stat.S_ISDIR(st.st_mode):
                    sub_dirs.append(full_path)
            except OSError as e:
                print(f"ls: cannot access '{full_path}': {os.strerror(e.errno)}", file=sys.stderr)

    if sys.stdout.isatty():
        print_columns(names)
    else:
        for name in names:
            print(name)

    success = True
    for sub in sub_dirs:
        print()
        if not list_directory(sub, opts, show_header=True):
            success = False

    return success

if __name__ == "__main__":
    opts = {
        'recursive': False,
        'reverse': False,
    }

    try:
        parsed_opts, args = getopt.getopt(sys.argv[1:], "Rr")
    except getopt.GetoptError as e:
        print(f"ls: invalid option -- '{e.opt}'", file=sys.stderr)
        sys.exit(1)

    for opt, _ in parsed_opts:
        if opt == '-R':
            opts['recursive'] = True
        elif opt == '-r':
            opts['reverse'] = True

    targets = args if args else ['.']
    exit_code = 0
    multiple_targets = len(targets) > 1

    for idx, target in enumerate(targets):
        if idx > 0:
            print()
        show_hdr = multiple_targets or opts['recursive']
        if not list_directory(target, opts, show_header=show_hdr):
            exit_code = 1

    sys.exit(exit_code)
