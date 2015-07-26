/*  exmplayer, GUI front-end for mplayer.
    Copyright (C) 2010-2015 Rupesh Sreeraman

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#include "languages.h"

Languages::Languages()
{
}
QMap<QString,QString> Languages::encodings() {

    QMap<QString,QString> mapLang;

    mapLang["UTF-16"] = tr("Unicode");
    mapLang["UTF-8"] = tr("UTF-8");
    mapLang["ISO-8859-1"] = tr("Western European Languages");
    mapLang["ISO-8859-15"] = tr("Western European Languages with Euro");
    mapLang["ISO-8859-2"] = tr("Slavic/Central European Languages");
    mapLang["ISO-8859-3"] = tr("Esperanto, Galician, Maltese, Turkish");
    mapLang["ISO-8859-4"] = tr("Old Baltic charset");
    mapLang["ISO-8859-5"] = tr("Cyrillic");
    mapLang["ISO-8859-6"] = tr("Arabic");
    mapLang["ISO-8859-7"] = tr("Modern Greek");
    mapLang["ISO-8859-9"] = tr( "Turkish");
    mapLang["ISO-8859-13"] = tr( "Baltic");
    mapLang["ISO-8859-14"] = tr( "Celtic");
    mapLang["ISO-8859-16"] = tr( "South-Eastern European");
    mapLang["ISO-8859-8"] = tr( "Hebrew charsets");
    mapLang["KOI8-R"] = tr( "Russian");
    mapLang["KOI8-U/RU"] = tr( "Ukrainian, Belarusian");
    mapLang["CP936"] = tr( "Simplified Chinese charset");
    mapLang["BIG5"] = tr( "Traditional Chinese charset");
    mapLang["SHIFT-JIS"] = tr( "Japanese charsets");
    mapLang["CP949"] = tr( "Korean charset");
    mapLang["CP874"] = tr( "Thai charset");
    mapLang["CP1251"] = tr( "Cyrillic Windows");
    mapLang["CP1250"] = tr( "Slavic/Central European Windows");
    mapLang["CP1256"] = tr( "Arabic Windows");
    mapLang["CP1253"] = tr("Modern Greek Windows");


    return mapLang;
}

QMap<QString,QString> Languages::LangList() {

    QMap<QString,QString> mapLang;

    mapLang["aa"] = tr("Afar");
    mapLang["ab"] = tr("Abkhazian");
    mapLang["ae"] = tr("Avestan");
    mapLang["af"] = tr("Afrikaans");
    mapLang["ak"] = tr("Akan");
    mapLang["am"] = tr("Amharic");
    mapLang["an"] = tr("Aragonese");
    mapLang["ar"] = tr("Arabic");
    mapLang["as"] = tr("Assamese");
    mapLang["av"] = tr("Avaric");
    mapLang["ay"] = tr("Aymara");
    mapLang["az"] = tr("Azerbaijani");
    mapLang["ba"] = tr("Bashkir");
    mapLang["be"] = tr("Belarusian");
    mapLang["bg"] = tr("Bulgarian");
    mapLang["bh"] = tr("Bihari");
    mapLang["bi"] = tr("Bislama");
    mapLang["bm"] = tr("Bambara");
    mapLang["bn"] = tr("Bengali");
    mapLang["bo"] = tr("Tibetan");
    mapLang["br"] = tr("Breton");
    mapLang["bs"] = tr("Bosnian");
    mapLang["ca"] = tr("Catalan");
    mapLang["ce"] = tr("Chechen");
    mapLang["co"] = tr("Corsican");
    mapLang["cr"] = tr("Cree");
    mapLang["cs"] = tr("Czech");
    mapLang["cu"] = tr("Church");
    mapLang["cv"] = tr("Chuvash");
    mapLang["cy"] = tr("Welsh");
    mapLang["da"] = tr("Danish");
    mapLang["de"] = tr("German");
    mapLang["dv"] = tr("Divehi");
    mapLang["dz"] = tr("Dzongkha");
    mapLang["ee"] = tr("Ewe");
    mapLang["el"] = tr("Greek");
    mapLang["en"] = tr("English");
    mapLang["eo"] = tr("Esperanto");
    mapLang["es"] = tr("Spanish");
    mapLang["et"] = tr("Estonian");
    mapLang["eu"] = tr("Basque");
    mapLang["fa"] = tr("Persian");
    mapLang["ff"] = tr("Fulah");
    mapLang["fi"] = tr("Finnish");
    mapLang["fj"] = tr("Fijian");
    mapLang["fo"] = tr("Faroese");
    mapLang["fr"] = tr("French");
    mapLang["fy"] = tr("Frisian");
    mapLang["ga"] = tr("Irish");
    mapLang["gd"] = tr("Gaelic");
    mapLang["gl"] = tr("Galician");
    mapLang["gn"] = tr("Guarani");
    mapLang["gu"] = tr("Gujarati");
    mapLang["gv"] = tr("Manx");
    mapLang["ha"] = tr("Hausa");
    mapLang["he"] = tr("Hebrew");
    mapLang["hi"] = tr("Hindi");
    mapLang["ho"] = tr("Hiri");
    mapLang["hr"] = tr("Croatian");
    mapLang["ht"] = tr("Haitian");
    mapLang["hu"] = tr("Hungarian");
    mapLang["hy"] = tr("Armenian");
    mapLang["hz"] = tr("Herero");
    mapLang["ch"] = tr("Chamorro");
    mapLang["ia"] = tr("Interlingua");
    mapLang["id"] = tr("Indonesian");
    mapLang["ie"] = tr("Interlingue");
    mapLang["ig"] = tr("Igbo");
    mapLang["ii"] = tr("Sichuan");
    mapLang["ik"] = tr("Inupiaq");
    mapLang["io"] = tr("Ido");
    mapLang["is"] = tr("Icelandic");
    mapLang["it"] = tr("Italian");
    mapLang["iu"] = tr("Inuktitut");
    mapLang["ja"] = tr("Japanese");
    mapLang["jv"] = tr("Javanese");
    mapLang["ka"] = tr("Georgian");
    mapLang["kg"] = tr("Kongo");
    mapLang["ki"] = tr("Kikuyu");
    mapLang["kj"] = tr("Kuanyama");
    mapLang["kk"] = tr("Kazakh");
    mapLang["kl"] = tr("Greenlandic");
    mapLang["km"] = tr("Khmer");
    mapLang["kn"] = tr("Kannada");
    mapLang["ko"] = tr("Korean");
    mapLang["kr"] = tr("Kanuri");
    mapLang["ks"] = tr("Kashmiri");
    mapLang["ku"] = tr("Kurdish");
    mapLang["kv"] = tr("Komi");
    mapLang["kw"] = tr("Cornish");
    mapLang["ky"] = tr("Kirghiz");
    mapLang["la"] = tr("Latin");
    mapLang["lb"] = tr("Luxembourgish");
    mapLang["lg"] = tr("Ganda");
    mapLang["li"] = tr("Limburgan");
    mapLang["ln"] = tr("Lingala");
    mapLang["lo"] = tr("Lao");
    mapLang["lt"] = tr("Lithuanian");
    mapLang["lu"] = tr("Luba-Katanga");
    mapLang["lv"] = tr("Latvian");
    mapLang["mg"] = tr("Malagasy");
    mapLang["mh"] = tr("Marshallese");
    mapLang["mi"] = tr("Maori");
    mapLang["mk"] = tr("Macedonian");
    mapLang["ml"] = tr("Malayalam");
    mapLang["mn"] = tr("Mongolian");
    mapLang["mo"] = tr("Moldavian");
    mapLang["mr"] = tr("Marathi");
    mapLang["ms"] = tr("Malay");
    mapLang["mt"] = tr("Maltese");
    mapLang["my"] = tr("Burmese");
    mapLang["na"] = tr("Nauru");
    mapLang["nb"] = trUtf8("Bokmål");
    mapLang["nd"] = tr("Ndebele");
    mapLang["ne"] = tr("Nepali");
    mapLang["ng"] = tr("Ndonga");
    mapLang["nl"] = tr("Dutch");
    mapLang["nn"] = tr("Norwegian Nynorsk");
    mapLang["no"] = tr("Norwegian");
    mapLang["nr"] = tr("Ndebele");
    mapLang["nv"] = tr("Navajo");
    mapLang["ny"] = tr("Chichewa");
    mapLang["oc"] = tr("Occitan");
    mapLang["oj"] = tr("Ojibwa");
    mapLang["om"] = tr("Oromo");
    mapLang["or"] = tr("Oriya");
    mapLang["os"] = tr("Ossetian");
    mapLang["pa"] = tr("Panjabi");
    mapLang["pi"] = tr("Pali");
    mapLang["pl"] = tr("Polish");
    mapLang["ps"] = tr("Pushto");
    mapLang["pt"] = tr("Portuguese");
    mapLang["qu"] = tr("Quechua");
    mapLang["rm"] = tr("Romansh");
    mapLang["rn"] = tr("Rundi");
    mapLang["ro"] = tr("Romanian");
    mapLang["ru"] = tr("Russian");
    mapLang["rw"] = tr("Kinyarwanda");
    mapLang["sa"] = tr("Sanskrit");
    mapLang["sc"] = tr("Sardinian");
    mapLang["sd"] = tr("Sindhi");
    mapLang["se"] = tr("Sami");
    mapLang["sg"] = tr("Sango");
    mapLang["si"] = tr("Sinhala");
    mapLang["sk"] = tr("Slovak");
    mapLang["sl"] = tr("Slovenian");
    mapLang["sm"] = tr("Samoan");
    mapLang["sn"] = tr("Shona");
    mapLang["so"] = tr("Somali");
    mapLang["sq"] = tr("Albanian");
    mapLang["sr"] = tr("Serbian");
    mapLang["ss"] = tr("Swati");
    mapLang["st"] = tr("Sotho");
    mapLang["su"] = tr("Sundanese");
    mapLang["sv"] = tr("Swedish");
    mapLang["sw"] = tr("Swahili");
    mapLang["ta"] = tr("Tamil");
    mapLang["te"] = tr("Telugu");
    mapLang["tg"] = tr("Tajik");
    mapLang["th"] = tr("Thai");
    mapLang["ti"] = tr("Tigrinya");
    mapLang["tk"] = tr("Turkmen");
    mapLang["tl"] = tr("Tagalog");
    mapLang["tn"] = tr("Tswana");
    mapLang["to"] = tr("Tonga");
    mapLang["tr"] = tr("Turkish");
    mapLang["ts"] = tr("Tsonga");
    mapLang["tt"] = tr("Tatar");
    mapLang["tw"] = tr("Twi");
    mapLang["ty"] = tr("Tahitian");
    mapLang["ug"] = tr("Uighur");
    mapLang["uk"] = tr("Ukrainian");
    mapLang["ur"] = tr("Urdu");
    mapLang["uz"] = tr("Uzbek");
    mapLang["ve"] = tr("Venda");
    mapLang["vi"] = tr("Vietnamese");
    mapLang["vo"] = trUtf8("Volapük");
    mapLang["wa"] = tr("Walloon");
    mapLang["wo"] = tr("Wolof");
    mapLang["xh"] = tr("Xhosa");
    mapLang["yi"] = tr("Yiddish");
    mapLang["yo"] = tr("Yoruba");
    mapLang["za"] = tr("Zhuang");
    mapLang["zh"] = tr("Chinese");
    mapLang["zu"] = tr("Zulu");

    return mapLang;
}

