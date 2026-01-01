# Usage

## As a subtree

Considerations:

- the library is in the `/data/Projects/RadioHead` directory
- the library will be added as a **subtree** in your project's `lib` directory

### Add the library

1. `cd` to your project's root directory

2. add a remote, `RadioHead_local` and fetch the library (`-f` flag):

```sh
git remote add -f RadioHead_local /data/Projects/RadioHead
```

3. add the library's branch you want:

```sh
# for main
git subtree add --prefix lib/RadioHead RadioHead_local main --squash
# for dev
git subtree add --prefix lib/RadioHead RadioHead_local dev --squash
```

### Update the library

1. `cd` to your project's root directory

2. fetch the new version

```sh
git fetch RadioHead_local
```

3. pull the library's branch you want:

```sh
# for main
git subtree pull --prefix lib/RadioHead RadioHead_local main --squash
# for dev
git subtree pull --prefix lib/RadioHead RadioHead_local dev --squash
```

## Test project

```sh
mkdir Test_RadioHead && cd "$_"

podman run -it --rm -v /data/platformio:/platformio:Z -v "${PWD}":/project:Z \
    pio project init --board esp32dev --project-option \
        "platform=https://github.com/pioarduino/platform-espressif32/releases/download/stable/platform-espressif32.zip"

git init && git add . && git commit -m 'Project initialized'

git remote add -f RadioHead_local /data/Projects/RadioHead

# for main
git subtree add --prefix lib/RadioHead RadioHead_local main --squash
# for dev
git subtree add --prefix lib/RadioHead RadioHead_local dev --squash
```

To update RadioHead, from `Test_RadioHead` directory run:

```sh
git fetch RadioHead_local

# for main
git subtree pull --prefix lib/RadioHead RadioHead_local main --squash
# for dev
git subtree pull --prefix lib/RadioHead RadioHead_local dev --squash
```

Create `src/main.cpp`, check one of `RadioHead/examples/` if needed, and compile, upload, ...

```sh
podman run -it --rm -v /data/platformio:/platformio:Z -v "${PWD}":/project:Z pio run

podman run -it --rm -v /data/platformio:/platformio:Z -v "${PWD}":/project:Z --device /dev/ttyUSB0 \
    pio run --target upload

podman run -it --rm -v /data/platformio:/platformio:Z -v "${PWD}":/project:Z --device /dev/ttyUSB0 \
    pio run --target monitor

podman run -it --rm -v /data/platformio:/platformio:Z -v "${PWD}":/project:Z pio run --target clean
```
