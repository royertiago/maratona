inputformat() {
    local target=$(dirname "$1")
    inputformat_files=$target/input/*
    inputformat_sed='sed s/input/output/'
}
