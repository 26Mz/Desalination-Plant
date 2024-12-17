# Desalination-Plant
Code, to use the desalination plant, by 26Mz, KSKreuzlingen.
These are the files to make own measurements.
Instructions:

1. First you will need an Arduino UNO, [Temperature Sensor](https://www.reichelt.com/ch/de/shop/produkt/entwicklerboards_-_temperatursensor_bis_125_c_ds18b20-215884) and a [Gravity Analog TDS Sensor](https://www.digikey.ch/de/products/detail/dfrobot/SEN0244/8019062?utm_adgroup=General&utm_source=google&utm_medium=cpc&utm_campaign=PMax:%20Smart%20Shopping_Product_Zombie%20SKUs&utm_term=&productid=8019062&utm_content=General&utm_id=go_cmp-18009722334_adg-_ad-__dev-c_ext-_prd-8019062_sig-Cj0KCQiAlsy5BhDeARIsABRc6ZueBWK31GQtArCRUrqrnsRifeVlWiIyak6mw4H3Xo9S1Rxm_mDAlOgaAgABEALw_wcB&gad_source=1&gclid=Cj0KCQiAlsy5BhDeARIsABRc6ZueBWK31GQtArCRUrqrnsRifeVlWiIyak6mw4H3Xo9S1Rxm_mDAlOgaAgABEALw_wcB). Also you will need a few jumper cables and a breadboard.
2. You measure 100 ml deionised water and put x gramms salt into the water.
3. Install python and the Arduino IDE.
4. For the python library you only use the "serial" library, to use the Arduino, you need to install [these Libraries](https://joy-it.net/files/files/Produkte/LK-Temp2/LK-Temp2_Arduino-Libraries.zip), and put them into: 
C:\Users\[YOUR USERNAME]\Documents\Arduino\libraries
5. Now you download the code files.
6. Aferward you upload you .ido file to the Arduino, but make sure, that no terminal is opened, after that you start the python file, that saves the measurements into data.txt.
