# C-Logger

Una libreria di logging per il linguaggio C, pensata per semplificare il debug e la tracciatura degli eventi in applicazioni console e server.

## Caratteristiche
- Abilita/disabilita l’output colorato sul terminale.
- Scrive su file di log in append, con timestamp e livello di gravità.
- Livelli di log configurabili: DEBUG, INFO, WARNING, ERROR.
- API semplice e macro per chiamate rapide (`log_debug`, `log_info`, …).

## Funzionalità in sviluppo (Work In Progress)
- **Thread safety**: rendere le operazioni di write atomiche in ambienti multi-thread.  
- **Personalizzazione del formato di data/ora**: possibilità di passare al logger una stringa personalizzata con `strftime`.

## TEST

### code
```c
#include <stdio.h>
#include "logger.h"

int main(){

    logger.init("log.txt", LOG_DEBUG, SHELL_ENABLE);

    logger.message(LOG_DEBUG, "%s %s", "ciao");

    log_debug("%s", "DIRECT ERROR!!");
    log_info("%s", "DIRECT INFO!!");
    log_warn("%s", "DIRECT WARNING!!");
    log_error("%s", "DIRECT ERROR!!");

    return 0;
}
```

### Output

shell<br/>
[07-05-2025 23:30:49]  $${\color{green}ciao}$$<br/>
[07-05-2025 23:30:49]  $${\color{green}DIRECT \space DEBUG!!}$$<br/>
[07-05-2025 23:30:49]  $${\color{blue}DIRECT \space INFO!!}$$<br/>
[07-05-2025 23:30:49]  $${\color{yellow}DIRECT \space WARNING!!}$$<br/>
[07-05-2025 23:30:49]  $${\color{red}DIRECT \space ERROR!!}$$<br/>

log.txt
```
[07-05-2025 23:30:49] (DEBUG): ciao 
[07-05-2025 23:30:49] (DEBUG): DIRECT ERROR!!
[07-05-2025 23:30:49] (INFO): DIRECT INFO!!
[07-05-2025 23:30:49] (WARNING): DIRECT WARNING!!
[07-05-2025 23:30:49] (ERROR): DIRECT ERROR!!
```