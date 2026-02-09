These are example files to quick start a project using the library.

Here is how to use these:

### Initialize a new project

In an empty folder:

```sh
podman run -it --rm -v /data/platformio:/platformio:Z -v "${PWD}":/project:Z \
    pio project init --board esp32dev --project-option \
        "platform=https://github.com/pioarduino/platform-espressif32/releases/download/stable/platform-espressif32.zip"
```

### Add required files

From this project copy:

- `platformio.ini`
- `partitions4M_1600_760_nk.csv`
- the `src` directory
- the `data` directory

in the new project's root folder.

### Initialize the git repository

In the new project's root folder:

```sh
git init
git add --all
git commit -m "Repository initialization"
```

### Add the library as a subtree

In the new project's root folder, add a remote for the subtree then add the library as subtree. Assuming that you use a local copy of the library located in the `/data/Projects/ESP32-BoardManager`, use:

```sh
git remote add ESP32-BoardManager /data/Projects/ESP32-BoardManager
git fetch ESP32-BoardManager
git subtree add --prefix lib/ESP32-BoardManager ESP32-BoardManager main --squash
```

### Do a test build of the project

```sh
podman run -it --rm -v /data/platformio:/platformio:Z -v "${PWD}":/project:Z pio run
```

### Library update

To add the newest version of the library in your project use:

```sh
git fetch ESP32-BoardManager
git subtree pull --prefix lib/ESP32-BoardManager \
    ESP32-BoardManager main --squash \
    -m "ESP32-BoardManager update"
```

### Update the library from another project

```sh
git subtree push --prefix lib/ESP32-BoardManager ESP32-BoardManager UpdateFromRemoteProject
```

the changes will go to the library's `UpdateFromRemoteProject` branch - this branch will be created if not exists.

To see the changes:

```sh
git checkout UpdateFromRemoteProject
git diff main
```
