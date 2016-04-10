TEMPLATE = aux

entries.path = /usr/share/jolla-settings/entries
entries.files = onyx-camera-settings.json

pages.path = /usr/share/jolla-settings/pages/onyx-camera-settings
pages.files = settings.qml camera-resolutions.json

translations.path = /usr/share/translations
translations.files = i18n/*.qm

system(lupdate . -ts $$PWD/i18n/onyx-camera-settings_eng_en.ts)
system(lrelease -idbased $$PWD/i18n/*.ts)

OTHER_FILES += \
    onyx-camera-settings.json \
    settings.qml \
    i18n/*.ts \
    camera-resolutions.json

TRANSLATIONS += i18n/*.ts
    
INSTALLS = entries pages translations
