import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

word=["misemise","koosaga","PaSsWORd","D3GwP2v","divNconQ","Hiiii","MelonCHT","minimini","Lucky","12345678","FireHole","iS","babo","YoU","are","idoIT","CODE","funny","404","Erebus","Sakupen","SW","Tidal","wAVE","Renn241","GeoDash","DIMRAIN","ORBIT","Robtop","James","Cubelver","ISPY","GANGnam","stylE","67676767","50000","4CHAd","67the69","A1b2c3D4","Aplus1","2p3wheN","I I I j","jjjjjjjj","How","Bbakjoon","Ruby1","Plat5","134340","Rate 5","39420","Output","Input","Casino","RaNDoM","maismais","2315f82g","23r8hFn","K3n","Cpp23","323684132","33faf825","NockEm","Jumper","Cycles","9circles","8o8o8o8o","BoBoBoBo0","NH22","Its Me","G3O GD","killbot","92fn2l2","74HC595","theVaULt","12345679","Im Dead","ImNo1","vamos","400","Im67Kid","Nojokes","Hate67","18263144","Mypwd","MySQL","MARIA db","solvedAC","ACcepted","slasla","nothinG","Lombi","Owo","uWu","ewe","RAWR80","Auto6285","Auto2590","Auto5192","Auto5388","Auto0284","Auto9206","Auto3514","3P141592","192p168","00000000","SCP096","BlueHell","Nowise","Kitty","Little","CraZy50","61448r","11718","sssooS","Magpile","Copyrln","Doogie","Impasta","2Creatpr","Likwtypo","kiwikiwi","23oufgq","Auto9999","Auto2331","Auto0356","Auto8882","Auto2442","Auto1312","Auto2263","Auto3358","Auto1938","Auto2000","Auto6713","NeXuS","Exen535","DyadGOAt","shiVer","XxXxXxXx","pyth0n","Reddit","GOLDEN","Auto6767","Auto7778","Auto2329","Auto3141","Auto5926","Auto5358","Auto9793","Shipjoon","Chunjoon","GongGang","o4rb8it","Firewa11","L293D","NONONONO","119","Physics","MathLike","2026","Unicode","Ahskiiy5","Blueskii","Jack1234","abcd0911","qwer1234","focUs","Amolgus","big2027","Sigsegv","MyError","print","exit 0","Aleph 0","NZEC","Auto3838","Auto3113","Sylveon","x73361f","INfinity","Cloud 9","Bapple","cherry","Blossom","na425140","Psisfun","20260330","SnowWhen","20251203","ahahah7","Ch0mp0","Navur","Y0ut9b3","G33gl6","T67itt3r","F2c3b44k","Da8m","TLE","Auto2945","Auto6394","Auto8362"]
word+=["Coding is fun","I am platinum 1","Math tags are good","This is the best testcase","My name is misemise","Have fun","Do you like 67 meme","Is this possible with accurate hitboxes","flamewall difficulty","1 plus 1 is 2","Im not an id1ot","Can you get AC","My hardest is Dyad","Dyad is better than Bloodbath","Krmal50 levels are so","234635624423456235234541","998244353s primitive root is 3","Time limit is too short you need Cpp","Dwarf planet 134340 is not a planet","Me when crashing at 99 percent","Colbreakz is my favorite","Sonic wave is in 30 tier in GDDL","There are more than 136919182 levels in Geometry Dash","I play pokemon legends ZA","Water 0n the H1ll","Koosaga and Cubelover playing nim g4me","A is for 65 and B is for 66 and C is for 67","There are 200 short words in the list","There are 30 sentences in the list","Testcase ac 1s s0000000000 g0000000d"]
word+=['is']*70
if random.random()<0.67:N=random.randint(1,100)
else:N=1
for X in range(N):
    L=0
    if N==1:words=random.randint(1,4)
    else:words=random.randint(1,20)
    for i in range(words):
        j=random.choice(word)
        L+=len(j)+1
        if L>100:break
        if i:print(' ',end='')
        print(j,end='')
    if X<N-1:print()
