#!/bin/bash

#set -ex

echo "...Checking chunguscoin.conf"

if [ ! -e "$HOME/.chunguscoin/chunguscoin.conf" ]; then
    mkdir -p $HOME/.chunguscoin

    echo "...Creating chunguscoin.conf"
    cat <<EOF > $HOME/.chunguscoin/chunguscoin.conf
rpcuser=${rpcuser:-chunguscoinrpc}
rpcpassword=${rpcpassword:-`dd if=/dev/urandom bs=33 count=1 2>/dev/null | base64`}
txindex=1
bind=${listenip:-127.0.0.1}
rpcbind=${listenip:-127.0.0.1}
EOF

    cat $HOME/.chunguscoin/chunguscoin.conf
fi

echo "...Checking fetch-params"
$HOME/zcutil/fetch-params.sh
echo "Initialization completed successfully"
echo

# ToDo: Needs some rework. I was sick
if [ $# -gt 0 ]; then

    args=("$@")

elif [  -z ${assetchain+x} ]; then

    args=("-gen -genproclimit=${genproclimit:-2} -pubkey=${pubkey}")

else

    args=("-pubkey=${pubkey} -ac_name=${assetchain} -addnode=${seednode}")

fi

echo
echo "****************************************************"
echo "Running: chunguscoind ${args[@]}"
echo "****************************************************"

exec chunguscoind ${args[@]}
