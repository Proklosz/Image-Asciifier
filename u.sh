# Remove program files
sudo rm -rf /usr/local/bin/AsciiGen

# Remove desktop shortcut
rm -f "$HOME/Asztal/AsciiGen.desktop"

# Inform the user
echo "Uninstallation complete."

# Prompt for user input to prevent the script from exiting immediately
read -p "Press Enter to exit..."
