# Goods Transport Services - C++ 11/14 -2020
C++ 11/14 Goods Transport Services, implement with Dijkstra algorithm. 

    run sim from terimnal example:

$ ./transferSimName -f < infile1> [ < infile2> < infile3> ... ][-p] < outfile>

    format of files input:

  < node>,<arrival_time>,<case_quantity>,<departure_time>
  
Example:

![image](https://user-images.githubusercontent.com/48412341/126071860-50948b63-a947-4575-ab57-1cf1197a3f2c.png)

    Commands:

[1] open,< fileName> - open file and update data.
    
   Example:
    
   ![image](https://user-images.githubusercontent.com/48412341/126072020-7f415e36-08a8-4b58-b818-d9ed60766f6e.png)

[2] < WarehouseName>,outbound - Finding a group of warehouses linked to the input warehouse.

   Example:
   
   ![image](https://user-images.githubusercontent.com/48412341/126072397-7d4bb566-8291-4d30-a741-3048a22beafd.png)

[3] < WarehouseName>,inbound - Finding a group of warehouses from which there is a link to the input warehouse.

   Example:
   
   ![image](https://user-images.githubusercontent.com/48412341/126072572-3ac1867c-9057-451b-927a-66c1fd65a552.png)

[4] < WarehouseName>,inventory,< Date> < Time> - The balance of crates in the warehouse at this time.

   Example:
   
   ![image](https://user-images.githubusercontent.com/48412341/126072833-22bfde5d-2889-41ec-af0c-e5625c64938c.png)

[5] < sourceWarehouse>,< targetWarehouse>,shortest - Calculate the shortest route between the two warehouses.

[6] print - print all data.
