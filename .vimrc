set autoindent
set ic
set nohlsearch
set nu
set incsearch
set tabstop=2
set keywordprg=sdcv
syntax on
map! kj <Esc>
:filetype plugin on
au BufReadPost * if line("'\"") > 0|if line("'\"") <= line("$")|exe("norm '\"")|else|exe "norm $"|endif|endif 
set helplang=cn
