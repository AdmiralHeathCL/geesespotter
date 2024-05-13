import os

LIBNAME = ["geesespotter_lib.cpp"]
PROGRAM = "geesespotter.cpp"

BUILD_DIR = "build"
FLAGS = "-O3 -Wall -Wpedantic"


def main():

    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    if not os.path.isdir(BUILD_DIR):
        os.mkdir(BUILD_DIR)

    objects = []

    for lib in LIBNAME:
        os.system(f"g++ -std=c++11 {lib} {FLAGS} -c -o {BUILD_DIR}/{lib.split('.')[0]}.o")
        objects.append(f"{BUILD_DIR}/{lib.split('.')[0]}.o")

    os.system(f"g++ -std=c++11 {PROGRAM} {FLAGS} -c -o {BUILD_DIR}/{PROGRAM.split('.')[0]}.o")
    objects.append(f"{BUILD_DIR}/{PROGRAM.split('.')[0]}.o")

    os.system(f"g++ {' '.join(objects)} {FLAGS} -o {BUILD_DIR}/{PROGRAM.split('.')[0]}.exe")

    os.chdir(BUILD_DIR)
    try:
        os.system(f"{PROGRAM.split('.')[0]}.exe")
    except KeyboardInterrupt:
        pass
    os.chdir("..")
    

if __name__ == "__main__":
    main()