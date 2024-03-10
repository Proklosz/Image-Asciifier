# Check if necessary dependencies are installed
if ! dpkg -s libgtkmm-3.0-dev >/dev/null 2>&1; then
    echo "Dependency: libgtkmm-3.0-dev is missing. Attempting to install..."
    sudo apt-get install -y libgtkmm-3.0-dev
else
    echo "libgtkmm-3.0-dev installed"
fi

if ! dpkg -s libopencv-dev >/dev/null 2>&1; then
    echo "Dependency: libopencv-dev is missing. Attempting to install..."
    sudo apt-get install -y libopencv-dev
else
    echo "libopencv-dev installed"
fi

# Copy program files to appropriate location
sudo cp -r ./AsciiGen /usr/local/bin || { echo "Failed to copy AsciiGen files."; exit 1; }
echo "Files copied"
# Set permissions
sudo chmod +x /usr/local/bin/AsciiGen/Ascii_art_maker || { echo "Failed to set permissions."; exit 1; }
echo "Permission given to executable"



sudo chmod +x ./UNINSTALL.sh || { echo "Failed to set permissions."; exit 1; }

sudo chmod +x ./u.sh || { echo "Failed to set permissions."; exit 1; }

# Get the path to the desktop directory using xdg-user-dirs-update
desktop_dir=$(xdg-user-dir DESKTOP)
echo "$desktop_dir"

# Create the desktop shortcut
cat << EOF > "$desktop_dir/AsciiGen.desktop"
[Desktop Entry]
Name=AsciiGen
Exec=/usr/local/bin/AsciiGen/Ascii_art_maker
Type=Application
Icon=/usr/local/bin/AsciiGen/icon.png
Categories=Utility;
Path=/usr/local/bin/AsciiGen
EOF

# Inform the user
echo "Installation complete."

echo "press ENTER to exit\n"
read anithing

