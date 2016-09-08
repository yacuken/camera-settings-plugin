TEMPLATE = subdirs

src_plugins.subdir = src/plugin
src_plugins.target = sub-plugins
src_plugins.depends = src

SUBDIRS += src src_plugins settings

OTHER_FILES += rpm/camera-settings-plugin.spec
