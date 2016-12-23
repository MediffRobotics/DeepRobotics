import pandas as pd
a='-12a,13b,'
b='14c;-13a,'
c='24b,25c;finish'

#Concatenating all
d=a+b+c

#spliting for each fram
e=d.split(';')

df=pd.DataFrame()



for i in e:
    j=i.split(',')
    if j[0] != 'finish':
        df_temp=pd.DataFrame(j)
        df=df.append(df_temp.T)    
        print df
    else:
        print j
    
