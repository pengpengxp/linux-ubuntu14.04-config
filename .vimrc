set autoindent
set nu
set incsearch
set hlsearch
set tabstop=2
set keywordprg=sdcv
syntax on
map! kj <Esc>
:filetype plugin on
au BufReadPost * if line("'\"") > 0|if line("'\"") <= line("$")|exe("norm '\"")|else|exe "norm $"|endif|endif 
set helplang=cn
