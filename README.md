# QT_mDNS_discovery
#Kullanılan Kütüphaneler:

https://github.com/emqx/qmqtt
qmake && make ile derlenip projeye modül olarak eklenmiştir.

https://github.com/nitroshare/qmdnsengine
cmake ile derlenip projeye dahil edilmiştir.


qmqtt örneklerinden faydalılarak QMQTT::Client sınıfından türetilen publisher ve subscriber sınıfları oluşturuldu.

Publisher veya subscribe sınıflarının herhangi birinden nesne oluşturulduktan sonra gönderilecek veri üye değişkeni 
olarak eklenen "payload" değişkenine yazılır diğer süreci sınıfın üye fonksiyonları yürütmektedir.

![Screenshot from 2023-01-09 02-20-18](https://user-images.githubusercontent.com/60985286/211224476-c76af164-325b-4ad4-bdcd-5fbc5cbafa2c.png)


#Update

Kullanılan yeni kütüphane:

https://github.com/eclipse/paho.mqtt.c
