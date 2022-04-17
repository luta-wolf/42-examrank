#!/bin/bash/
# Colors
blue=$'\033[0;34m'
cyan=$'\033[1;96m'
reset=$'\033[0;39m'

# Avoid boring prefix in du/df/etc
cd $HOME

initial_used_space=$(df -h $HOME | grep -v 'Filesystem' | awk '{ printf("%f", $3) }')

# Show current used space
initial_df=$(df -h . | grep --color=always -E "Size|Used|Avail|Capacity|[0-9]*\.*[0-9]*Mi|[0-9]*\.*[0-9]*Gi|[0-9]+\.*[0-9]+% |$")
echo "${blue}Current space:\n${reset}${initial_df}${reset}"
echo "${blue}\nHome folder:${reset}"
du -hd1 . 2>/dev/null | sort -h | grep --color=always "[0-9]*\.*[0-9]*M\t\|[0-9]*\.*[0-9]*G\t\|$"
echo ""

echo '----------------------'
echo 'Size    Used    Avail'
echo '----------------------'
df -h | grep Users | awk '{print $2 " = " $3 " + "  $4}'
rm -rf ~/Library/Application\ Support/Slack/Code\ Cache/
rm -rf ~/Library/Application\ Support/Slack/Cache/
rm -rf ~/Library/Application\ Support/Slack/Service\ Worker/CacheStorage/
#rm -rf ~/Library/ApplicationSupport/CrashReporter/*
#rm -rf ~/Library/Application\ Support/Code/*
#rm -rf ~/Library/Group\ Containers/*
rm -rf ~/Library/42_cache/
rm -rf ~/Library/Caches/CloudKit
rm -rf ~/Library/Caches/com.apple.akd
rm -rf ~/Library/Caches/com.apple.ap.adprivacyd
rm -rf ~/Library/Caches/com.apple.appstore
rm -rf ~/Library/Caches/com.apple.appstoreagent
rm -rf ~/Library/Caches/com.apple.cache_delete
rm -rf ~/Library/Caches/com.apple.commerce
rm -rf ~/Library/Caches/com.apple.iCloudHelper
rm -rf ~/Library/Caches/com.apple.imfoundation.IMRemoteURLConnectionAgent
rm -rf ~/Library/Caches/com.apple.keyboardservicesd
rm -rf ~/Library/Caches/com.apple.nbagent
rm -rf ~/Library/Caches/com.apple.nsservicescache.plist
rm -rf ~/Library/Caches/com.apple.nsurlsessiond
rm -rf ~/Library/Caches/storeassetd
rm -rf ~/Library/Caches/com.microsoft.VSCode.ShipIt
rm -rf ~/Library/Caches/com.microsoft.VSCode
rm -rf ~/Library/Caches/com.google.SoftwareUpdate
rm -rf ~/Library/Caches/com.google.Keystone
rm -rf ~/Library/Caches/com.apple.touristd
rm -rf ~/Library/Caches/com.apple.tiswitcher.cache
rm -rf ~/Library/Caches/com.apple.preferencepanes.usercache
rm -rf ~/Library/Caches/com.apple.preferencepanes.searchindexcache
rm -rf ~/Library/Caches/com.apple.parsecd
rm -rf ~/Library/Caches/
rm -rf ~/Library/Caches/
rm -rf ~/Library/Caches/
rm -rf ~/Library/Caches/
rm -rf ~/Library/Caches/
rm -rf ~/Library/Caches/
rm -rf ~/.Trash/*
rm -rf ~/.kube/cache/*
rm -rf ~/Library/Containers/com.docker.docker/Data/vms/*
rm -rf ~/Library/Application\ Support/Firefox/Profiles/hdsrd79k.default-release/storage
rm -rf ~/Library/42_cache
rm -rf ~/Library/Application\ Support/Slack/Service\ Worker/CacheStorage/
rm -rf ~/Library/Application\ Support/Slack/Cache/
rm -rf ~/Library/Application\ Support/Slack/Code\ Cache/
rm -rf ~/Library/Application\ Support/Code/User/workspaceStorage
rm -rf ~//Library/Application\ Support/Spotify/PersistentCache
rm -rf ~/Library/Application\ Support/Telegram\ Desktop/tdata/user_data
rm -rf ~/Library/Application\ Support/Telegram\ Desktop/tdata/emoji
rm -rf ~/Library/Application\ Support/Code/Cache/Library/Application\ Support/Code/Cachei
rm -rf ~/Library/Application\ Support/Code/CacheData
rm -rf ~/Library/Application\ Support/Code/Cache
rm -rf ~/Library/Application\ Support/Code/CacheData
rm -rf ~Library/Application\ Support/Code/Crashpad/completed

df -h | grep Users | awk '{print $2 " = " $3 " + "  $4}'
echo '----------------------'
echo "Clean Success"
