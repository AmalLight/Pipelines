#!/bin/bash

sudo apt install -y r-base

sudo apt install -y libxml2-dev libcurl4-openssl-dev # for Tidyverse

sudo Rscript -e 'install.packages ( "curl"        )' # dependency
sudo Rscript -e 'install.packages ( "rprojroot"   )' # dependency
sudo Rscript -e 'install.packages ( "desc"        )' # dependency
sudo Rscript -e 'install.packages ( "askpass"     )' # dependency
sudo Rscript -e 'install.packages ( "openssl"     )' # dependency
sudo Rscript -e 'install.packages ( "credentials" )' # dependency
sudo Rscript -e 'install.packages ( "sys"         )' # dependency
sudo Rscript -e 'install.packages ( "gert"        )' # dependency
sudo Rscript -e 'install.packages ( "usethis"     )' # dependency
sudo Rscript -e 'install.packages ( "fastmap"     )' # dependency
sudo Rscript -e 'install.packages ( "cachem"      )' # dependency
sudo Rscript -e 'install.packages ( "memoise"     )' # dependency
sudo Rscript -e 'install.packages ( "ps"          )' # dependency
sudo Rscript -e 'install.packages ( "processx"    )' # dependency
sudo Rscript -e 'install.packages ( "callr"       )' # dependency
sudo Rscript -e 'install.packages ( "prettyunits" )' # dependency
sudo Rscript -e 'install.packages ( "pkgbuild"    )' # dependency
sudo Rscript -e 'install.packages ( "testthat"    )' # dependency
sudo Rscript -e 'install.packages ( "pkgload"     )' # dependency
sudo Rscript -e 'install.packages ( "remotes"     )' # dependency
sudo Rscript -e 'install.packages ( "sessioninfo" )' # dependency
sudo Rscript -e 'install.packages ( "devtools"    )' # -devtools-

sudo Rscript -e 'install.packages ( "base" )' # functions for system invocation

sudo Rscript -e 'install.packages ( "magrittr"    )' # dependency
sudo Rscript -e 'install.packages ( "rlang"       )' # dependency
sudo Rscript -e 'install.packages ( "insight"     )' # dependency
sudo Rscript -e 'install.packages ( "sjlabelled   )' # dependency

sudo Rscript -e 'install.packages ( "sjmisc" )' # in pattern and string containers

sudo Rscript -e 'install.packages ( "bit"         )' # dependency
sudo Rscript -e 'install.packages ( "bit64"       )' # dependency
sudo Rscript -e 'install.packages ( "crayon"      )' # dependency
sudo Rscript -e 'install.packages ( "ellipsis"    )' # dependency
sudo Rscript -e 'install.packages ( "vctrs"       )' # dependency
sudo Rscript -e 'install.packages ( "lifecycle"   )' # dependency
sudo Rscript -e 'install.packages ( "pkgconfig"   )' # dependency
sudo Rscript -e 'install.packages ( "hms"         )' # dependency
sudo Rscript -e 'install.packages ( "R6"          )' # dependency
sudo Rscript -e 'install.packages ( "fansi"       )' # dependency
sudo Rscript -e 'install.packages ( "utf8"        )' # dependency
sudo Rscript -e 'install.packages ( "pillar"      )' # dependency
sudo Rscript -e 'install.packages ( "tibble"      )' # dependency
sudo Rscript -e 'install.packages ( "glue"        )' # dependency
sudo Rscript -e 'install.packages ( "purrr"       )' # dependency
sudo Rscript -e 'install.packages ( "tidyselect"  )' # dependency
sudo Rscript -e 'install.packages ( "tzdb"        )' # dependency

sudo Rscript -e 'install.packages ( "readr" )' # read any file version fileX.endY

sudo Rscript -e 'install.packages ( "proftools"   )' # dependency
sudo Rscript -e 'install.packages ( "NCmisc"      )' # dependency

sudo Rscript -e 'install.packages ( "reader" )' # readlines from files or inputs

sudo Rscript -e 'install.packages ( "stringi" )' # dependency
sudo Rscript -e 'install.packages ( "stringr" )' # functions specialized in strings

sudo Rscript -e 'install.packages ( "generics"   )' # dependency
sudo Rscript -e 'install.packages ( "dplyr"      )' # dependency
sudo Rscript -e 'install.packages ( "tidyr"      )' # dependency
sudo Rscript -e 'install.packages ( "backports"  )' # dependency
sudo Rscript -e 'install.packages ( "broom"      )' # dependency
sudo Rscript -e 'install.packages ( "DBI"        )' # dependency
sudo Rscript -e 'install.packages ( "assertthat" )' # dependency
sudo Rscript -e 'install.packages ( "forcats"    )' # dependency
sudo Rscript -e 'install.packages ( "dbplyr"     )' # dependency
sudo Rscript -e 'install.packages ( "gtable"     )' # dependency
sudo Rscript -e 'install.packages ( "colorspace" )' # dependency
sudo Rscript -e 'install.packages ( "munsell"    )' # dependency
sudo Rscript -e 'install.packages ( "scales"     )' # dependency
sudo Rscript -e 'install.packages ( "withr"      )' # dependency
sudo Rscript -e 'install.packages ( "ggplot2"    )' # dependency
sudo Rscript -e 'install.packages ( "haven"      )' # dependency
sudo Rscript -e 'install.packages ( "httr"       )' # dependency
sudo Rscript -e 'install.packages ( "jsonlite"   )' # dependency
sudo Rscript -e 'install.packages ( "lubridate"  )' # dependency
sudo Rscript -e 'install.packages ( "modelr"     )' # dependency
sudo Rscript -e 'install.packages ( "Rcpp"       )' # dependency
sudo Rscript -e 'install.packages ( "cellranger" )' # dependency
sudo Rscript -e 'install.packages ( "readxl"     )' # dependency
sudo Rscript -e 'install.packages ( "fs"         )' # dependency
sudo Rscript -e 'install.packages ( "reprex"     )' # dependency
sudo Rscript -e 'install.packages ( "xml2"       )' # dependency
sudo Rscript -e 'install.packages ( "rvest"      )' # dependency
sudo Rscript -e 'install.packages ( "rstudioapi" )' # dependency

sudo Rscript -e 'install.packages ( "tidyverse" )' # default pipe and other functions

