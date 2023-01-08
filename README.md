# QT_mDNS_discovery
#Kullanılan Kütüphaneler:

https://github.com/emqx/qmqtt
qmake && make ile derlenip projeye modül olarak eklenmiştir.

https://github.com/nitroshare/qmdnsengine
cmake ile derlenip projeye dahil edilmiştir.


qmqtt örneklerinden faydalılarak QMQTT::Client sınıfından türetilen publisher ve subscriber sınıfları oluşturuldu.

Publisher veya subscribe sınıflarının herhangi birinden nesne oluşturulduktan sonra gönderilecek veri üye değişkeni 
olarak eklenen "payload" değişkenine yazılır diğer süreci sınıfın üye fonksiyonları yürütmektedir.

