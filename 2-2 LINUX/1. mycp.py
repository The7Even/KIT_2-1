import os, sys, errno, getopt, stat

BUFFER_SIZE = 1024

def my_copy(src, dist):
    try:
        src_st = os.stat(src)
    except OSError as e:
        print(f"cp: cannot stat '{src}': {os.strerror(e.errno)}", file=sys.stderr)
        return False

    if stat.S_ISDIR(src_st.st_mode):
        print(f"cp: -r not specified; omitting directory '{src}'", file=sys.stderr)
        sys.exit(1)

    try:
        dist_st = os.stat(dist)
        if stat.S_ISDIR(dist_st.st_mode):
            dist = os.path.join(dist, os.path.basename(src.rstrip('/')))

            try:
                sub_st = os.stat(dist)
                if stat.S_ISDIR(sub_st.st_mode):
                    print(f"cp: cannot overwrite directory '{dist}' with non-directory", file=sys.stderr)
                    sys.exit(1)
                if os.path.samestat(src_st, sub_st):
                    print(f"cp: '{src}' and '{dist}' are the same file", file=sys.stderr)
                    sys.exit(1)
            except FileNotFoundError:
                pass
            
        else:
            if os.path.samestat(src_st, dist_st):
                print(f"cp: '{src}' and '{dist}' are the same file", file=sys.stderr)
                return False
    except FileNotFoundError:
        pass
    except OSError as e:
        print(f"cp: cannot stat '{dist}': {os.strerror(e.errno)}", file=sys.stderr)
        sys.exit(1)

    mode = stat.S_IMODE(src_st.st_mode)

    src_fd = -1
    dist_fd = -1

    try:
        src_fd = os.open(src, os.O_RDONLY)
        dist_fd = os.open(dist, os.O_WRONLY | os.O_CREAT | os.O_TRUNC, mode)

        while True:
            chunk = os.read(src_fd, BUFFER_SIZE)
            if not chunk:
                break
            
            total_written = 0
            while total_written < len(chunk):
                written = os.write(dist_fd, chunk[total_written:])
                total_written += written

        os.fchmod(dist_fd, mode)
        return True

    except OSError as e:
        print(f"cp: error copying '{src}' to '{dist}': {os.strerror(e.errno)}", file=sys.stderr)
        sys.exit(1)

    finally:
        if src_fd != -1:
            os.close(src_fd)
        if dist_fd != -1:
            os.close(dist_fd)

def cp_dir_R(src, dist):
    try:
        src_st = os.stat(src)
    except OSError as e:
        print(f"cp: cannot stat '{src}': {os.strerror(e.errno)}", file=sys.stderr)
        return False

    try:
        dist_st = os.stat(dist)
        if stat.S_ISDIR(dist_st.st_mode):
            target_dir = os.path.join(dist, os.path.basename(src.rstrip('/')))
        else:
            print(f"cp: cannot overwrite non-directory '{dist}' with directory '{src}'", file=sys.stderr)
            return False
    
    except FileNotFoundError:
        target_dir = dist
    except OSError as e:
        print(f"cp: cannot stat '{dist}': {os.strerror(e.errno)}", file=sys.stderr)
        return False

    abs_src = os.path.abspath(src)
    abs_target = os.path.abspath(target_dir)
    if abs_target == abs_src or abs_target.startswith(abs_src + os.sep):
        print(f"cp: cannot copy a directory, '{src}', into itself, '{target_dir}'", file=sys.stderr)
        return False

    mode = stat.S_IMODE(src_st.st_mode)
    try:
        target_st = os.stat(target_dir)
        if not stat.S_ISDIR(target_st.st_mode):
            print(f"cp: cannot overwrite non-directory '{target_dir}' with directory '{src}'", file=sys.stderr)
            return False
    except FileNotFoundError:
        try:
            os.mkdir(target_dir, mode)
        except OSError as e:
            print(f"cp: cannot create directory '{target_dir}': {os.strerror(e.errno)}", file=sys.stderr)
            return False

    success = True
    try:
        with os.scandir(src) as entries:
            for entry in entries:
                child_src = os.path.join(src, entry.name)
                child_dist = os.path.join(target_dir, entry.name)

                try:
                    child_st = os.stat(child_src)
                except OSError as e:
                    print(f"cp: cannot stat '{child_src}': {os.strerror(e.errno)}", file=sys.stderr)
                    success = False
                    continue

                if stat.S_ISDIR(child_st.st_mode):
                    if not cp_dir_R(child_src, child_dist):
                        success = False
                else:
                    if not my_copy(child_src, child_dist):
                        success = False

            os.chmod(target_dir, mode)
    except OSError as e:
        print(f"cp: error reading directory '{src}': {os.strerror(e.errno)}", file=sys.stderr)
        success = False

    return success

if __name__ == "__main__":
    recursive = False
    try:
        opts, args = getopt.getopt(sys.argv[1:], "r")
    except getopt.GetoptError as e:
        print(f"cp: invalid option -- '{e.opt}'", file=sys.stderr)
        sys.exit(1)

    for opt, _ in opts:
        if opt in ("-r", "-R"):
            recursive = True

    if len(args) == 0:
        print("cp: missing file operand", file=sys.stderr)
        sys.exit(1)
    elif len(args) == 1:
        print(f"cp: missing destination file operand after '{args[0]}'", file=sys.stderr)
        sys.exit(1)
    
    sources = args[:-1]
    dist = args[-1]

    if len(sources) > 1:
        try:
            dist_st = os.stat(dist)
            if not stat.S_ISDIR(dist_st.st_mode):
                print(f"cp: target '{dist}' is not a directory", file=sys.stderr)
                sys.exit(1)
        except OSError as e:
            print(f"cp: target '{dist}' is not a directory", file=sys.stderr)
            sys.exit(1)

    exit_code = 0
    for src in sources:
        try:
            src_st = os.stat(src)
        except OSError as e:
            print(f"cp: cannot stat '{src}': {os.strerror(e.errno)}", file=sys.stderr)
            exit_code = 1
            continue

        if stat.S_ISDIR(src_st.st_mode):
            if not recursive:
                print(f"cp: -r not specified; omitting directory '{src}'", file=sys.stderr)
                exit_code = 1
            else:
                if not cp_dir_R(src, dist):
                    exit_code = 1
        else:
            if not my_copy(src, dist):
                exit_code = 1

    sys.exit(exit_code)
