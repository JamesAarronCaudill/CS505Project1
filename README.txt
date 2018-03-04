This project simulates parts of MAC and DAC by allowing users control over sharing of tables they have created (and allowing further sharing via grant access) while also implementing the security officer user, who has an ability to control the forbidden and authorized tables directly.

We implemented forbidden and authorized tables using multiple vectors, where each vector holds one part of the table. By adding and removing from these vectors all at the same time, we can keep the data organized.

To build the program, use the accompanying Makefile.

When running the program, a prompt will appear. This prompt will give you all possible commands plus their numerical abbreviation. Either typing the command or typing the number corresponding with the command will run the command. Follow the instructions that the program gives you to successfully run the command.

Functions are documented within main(), in a comment section just above each function's implementation.
