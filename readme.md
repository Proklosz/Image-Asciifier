          BB
          BB
          BB
          BB    BB  @@@@    @@@@      BB@@pp        nn@@@@@@    $$$$''
          @@    @@@@  @@@@@@  @@@@  @@@@MM@@@@    @@@@@@$$    $$$$  $$$$
          BB    BB      @@      @@  ..    <<@@  @@@@    @@    @@      $$
          BB    BB      @@      @@      @@@@@@    @@    @@  @@$$$$$$$$$$
          BB    BB      @@      @@  WW@@  ;;@@      @@@@      $$
          BB    @@      @@      @@  @@@@  %%@@    @@          $$$$    $$
          BB    @@      @@      @@    @@@@  @@,,  @@@@$$$$      $$$$$$
                                                @@      $$@@
                                                @@      @@@@
                                                  @@@@@@@@

              ..BB                                        **@@$$
              @@BB                                @@@@    @@    $$
              BBBB@@                                      @@
            BBBB  BB        CC@@@@        @@@@    @@@@  @@@@@@  $$      &&$$$$      $$  $$$$
            BB    @@@@      @@  %%XX  //@@88  @@  @@@@  %%@@%%  @@    $$$$  $$$$    $$$$,,$$
          @@BB      BB      @@        @@          @@@@    @@    $$    $$      $$    $$
          BBBBBBBBBBBB@@      @@@@    @@          @@@@    @@    $$    $$$$$$$$$$    $$
        ^^BB          @@        @@@@  @@          @@@@    @@    @@    @@            $$
        BB&&          @@  ""@@  @@@@  %%@@MM  @@  @@@@    @@    @@    @@$$    $$    $$
        BB            %%@@  @@@@@@        @@@@@@  @@@@    @@    @@      @@$$@@``    $$

## Dependencies (if not installed)

### gtkmm :

```bash
sudo apt-get install libgtkmm-3.0-dev

```

### opencv :

```bash
sudo apt-get install libopencv-dev

```

## Build

```bash
    g++ -o Asciigen Asciigen.cpp `pkg-config --cflags --libs gtkmm-3.0` `pkg-config --cflags --libs opencv4`
```

## Run

```bash
    ./Asciigen
```
