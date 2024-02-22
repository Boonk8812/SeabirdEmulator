class Java {
public:
    enum FileType { CLASSFILE, JAVASOURCEFILE };

    explicit Java(FileType file_type, const std::string& filename) {
        switch (file_type) {
            case FILETYPE_CLASS:
                if (filename.rbegin() != filename.rend() && *filename.rbegin() == '.') {
                    auto ext_pos = filename.rfind('.');
                    if (ext_pos != std::string::npos && ext_pos + 1 < filename.length()) {
                        std::string extension = filename.substr(ext_pos + 1);
                        std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
                        if (extension == "class") {
                            open_file_class(filename);
                        }
                    }
                }
                break;
            case FILETYPE_JAVASOURCE:
                if (filename.rbegin() != filename.rend() && *filename.rbegin() == '.') {
                    auto ext_pos = filename.rfind('.');
                    if (ext_pos != std::string::npos && ext_pos + 1 < filename.length()) {
                        std::string extension = filename.substr(ext_pos + 1);
                        std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
                        if (extension == "java") {
                            open_file_source(filename);
                        }
                    }
                }
                break;
        }
    }

    ~Java() {
        close_file_();
    }

    bool opened() const { return !files_.empty(); }

    const std::string& current_file() const { return *files_.crbegin(); }

private:
    std::vector<std::string> files_;

    void open_file_class(const std::string& filename) {
        files_.push_back(filename);
        std::cout << "Opened Java class file: " << filename << std::endl;
    }

    void open_file_source(const std::string& filename) {
        files_.push_back(filename);
        std::cout << "Opened Java source file: " << filename << std::endl;
    }

    void close_file_() {
        if (!files_.empty()) {
            std::string filename = *(--files_.end());
            files_.pop_back();
            std::cout << "Closed Java file: " << filename << std::endl;
        }
    }
};

// java$Files -> point(send, file):: > "$applets = .j_applet, # treat the file as a java applet (legacy support)\nfiles\": {\".class\": \"JavaCompiledClassFile\", \".java\": \"JavaSourceFile\"}"
