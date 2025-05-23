# Read/Write SRAM (HM62256ALP-10) Using Arduino Mega 2560

This is one of my small projects to read and write to the `HM62256ALP-10` SRAM using an Arduino Mega 2560. The SRAM ICs were sourced from AliExpress at a reasonable price. I initially wrote the basic code with the help of ChatGPT and then refined it further. If you plan to run this code, I highly recommend using **PlatformIO** for a smoother development experience.

<img src="/lib/images/ic.jpg" height="150px"/> <img src="/lib/images/mega-2560.jpg" height="150px"/> <img src="/lib/images/setup.jpg" height="150px"/>

### Pin Configuration

| **Function**       | **Arduino Pin** | **SRAM Pin** | **Description**                              |
| ------------------ | --------------- | ------------ | -------------------------------------------- |
| Address A0-A14     | 22-36           | 1-15         | Address bus for 32KB memory space            |
| Data D0-D7         | 2-9             | 10-17        | 8-bit data bus                               |
| Chip Select (CS)   | 37              | 20           | Active low, enables the SRAM chip            |
| Output Enable (OE) | 38              | 22           | Active low, enables data output during reads |
| Write Enable (WE)  | 39              | 21           | Active low, enables data input during writes |
| Ground (GND)       | GND             | 14           | Ground connection                            |
| VCC (5V)           | 5V              | 28           | Power supply                                 |

### Commands

* **Read Data**

  ```
  read=address
  ```

  Reads a byte from the specified 16-bit memory address. The address should be in hexadecimal format (e.g., `read=0x1234`).

* **Write Data**

  ```
  write=address,data
  ```

  Writes a byte to the specified 16-bit memory address. Both address and data should be in hexadecimal format (e.g., `write=0x1234,0xAB`).

* **Example Usage**

  ```
  read=0x0000      # Read the first byte
  write=0x0000,0xAB # Write 0xAB to the first byte
  read=0x0000      # Verify the written data
  ```

### Notes

* Make sure to connect the GND and VCC pins correctly to avoid damage to the SRAM IC.
* Use short, clean jumper wires to reduce noise and ensure reliable data transfer.
* PlatformIO is recommended for better code structure and project management.

### License

This project is open source. Feel free to modify and use it as you like. Contributions are welcome.

Thank you!
