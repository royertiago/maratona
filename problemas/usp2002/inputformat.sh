inputformat() {
    local target=$(remove_extension "$1")
    inputformat_files=$target.in*
    inputformat_sed='sed s/\.in/\.sol/'
}
