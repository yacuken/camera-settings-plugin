TEMPLATE = aux

entries.path = /usr/share/jolla-settings/entries
entries.files = camera-settings.json

pages.path = /usr/share/jolla-settings/pages/camera-settings-plugin
pages.files = settings.qml

translations.path = /usr/share/translations
translations.files = i18n/*.qm

system(lupdate . -ts $$PWD/i18n/camera-settings_eng_en.ts)
system(lrelease -idbased $$PWD/i18n/*.ts)

OTHER_FILES += \
    camera-settings.json \
    settings.qml \
    i18n/*.ts

TRANSLATIONS += i18n/*.ts
    
INSTALLS = entries pages translations
