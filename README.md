## Usage

To use the library in a project see the `README.md` from the `/examples/QuickStartFiles` directory

## Build and upload

```sh
podman run -it --rm -v /data/platformio:/platformio:Z -v "${PWD}":/project:Z pio run --target clean

podman run -it --rm -v /data/platformio:/platformio:Z -v "${PWD}":/project:Z pio run

# podman run -it --rm -v /data/platformio:/platformio:Z -v "${PWD}":/project:Z --device /dev/ttyUSB0 pio run --target erase

podman run -it --rm -v /data/platformio:/platformio:Z -v "${PWD}":/project:Z --device /dev/ttyUSB0 pio run --target uploadfs

podman run -it --rm -v /data/platformio:/platformio:Z -v "${PWD}":/project:Z --device /dev/ttyUSB0 pio run --target upload

podman run -it --rm -v /data/platformio:/platformio:Z -v "${PWD}":/project:Z --device /dev/ttyUSB0 pio run --target monitor
```

## License

The software and documentation are released under the [GNU GPLv3](http://www.gnu.org/licenses/gpl-3.0.html) License. See the __LICENSE-GPLv3.txt__ file.
