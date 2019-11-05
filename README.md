# Sumo2Unreal

### Introduction
This project is an importer for [SUMO](http://sumo.dlr.de/wiki/Sumo_at_a_Glance)'s .net.xml road network files into the Unreal Engine 4 environment. This is important to bridge the capabilities of SUMO as a road network generator/convertor and traffic simulator to the Unreal Engine which is the preferred choice to create simulation software for testing self-driving cars.

The input taken by this importer is a SUMO's .net.xml road network file format and the output is a network of roads on the Unreal Editor. The .net.xml file is created using [NETGENERATE](http://sumo.dlr.de/wiki/NETGENERATE). The files created using NETGENERATE can be viewed using [NETEDIT](http://sumo.dlr.de/wiki/NETEDIT). We have provided some files which we generated in the [S2U_Screenshots](https://github.com/AugmentedDesignLab/Sumo2Unreal/tree/master/S2U_Screenshots) folder.

---

### Interesting Results
#### 1. Small spider network - 

NETGENERATE Command - 
```
netgenerate --spider --spider.arm-number=4 --spider.circle-number=3 --spider.space-radius=100 --output-file=MySUMOFile.net.xml
```
(The output by default goes into the 'net.net.xml' file, but you can add a -o parameter to specify file name)

Output as seen on NETEDIT Application - 
![spider01_netedit](https://github.com/AugmentedDesignLab/Sumo2Unreal/blob/master/S2U_Screenshots/spider01_netedit.png)

Output on the Unreal Editor after running our importer - 
![spider01_unreal](https://github.com/AugmentedDesignLab/Sumo2Unreal/blob/master/newTests/diamond-spider.png)

#### 2. Large Spider Network 

NETGENERATE Command 
```
netgenerate --spider
```

Output - 
![spider02_unreal](https://github.com/AugmentedDesignLab/Sumo2Unreal/blob/master/newTests/regularSpiderWeb.png)

#### 3. Basic Grid Network 

NETGENERATE Command 
```
netgenerate --grid
```

Output - 
![grid01_unreal](https://github.com/AugmentedDesignLab/Sumo2Unreal/blob/master/S2U_Screenshots/grid01.png)

#### 4. A Random Network 

NETGENERATE Command  
```
netgenerate --rand
```
Output - 
![rand_unreal](https://github.com/AugmentedDesignLab/Sumo2Unreal/blob/master/S2U_Screenshots/rand_network.png)

#### 5. A town map

XML file obtained from a [SUMO tutorial](http://sumo.sourceforge.net/userdoc/Tutorials/Import_from_OpenStreetMap.html) in which an OSM file was imported into SUMO. This was imported into UE4 using this importer.

Output - 
![real_town](https://github.com/AugmentedDesignLab/Sumo2Unreal/blob/master/S2U_Screenshots/real_town_ue4.png)

#### 6. Townsimpy 

XML files generated using [town-sim-py](https://github.com/AugmentedDesignLab/town-sim-py) which were then imported into UE4 using this importer.

Outputs - 
![townsimpy01](https://github.com/AugmentedDesignLab/Sumo2Unreal/blob/master/S2U_Screenshots/townsimpy_01_ue4.png)
![townsimpy02](https://github.com/AugmentedDesignLab/Sumo2Unreal/blob/master/S2U_Screenshots/townsimpy_02_ue4.png)

---

### Getting Started 

1. Please have a look at the [wiki pages](https://github.com/AugmentedDesignLab/Sumo2Unreal/wiki) for requirements, instructions on how to run the code and resources to learn if you want to contribute. 

2. Track our progress [here](https://github.com/AugmentedDesignLab/Sumo2Unreal/projects/1).

---

### References
For selecting the correct order of vertices for creating triangles, we are using the [earcut](https://github.com/mapbox/earcut.hpp) polygon triangulation library


