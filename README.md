# Castle-War-Game-Simulation
## GUI
![](https://github.com/AlyNasr/Castle-War-Game-Simulation/blob/main/simulation.gif)  

Four towers are defending the castle against enemies. Each tower guards one region (A, B, C or D) and can shoot only enemies in its region.  
Each region has a paved distance, colored "Khaki" in the above GUI, where enemies are allowed to move towards the tower only in the paved distance.  

There are 3 types of enemies:  
1. **Pavers:** Blue color, they are responsible for paving more distance towards the towers.  
2. **Fighters:** Green color, they attack the tower of their region causing damage that affects the tower health.  
3. **Shielded Fighters:** Orange color, they also attack the tower of their region but cause double the damage caused by the normal fighters. 
 
A tower also attacks the enemies of its region causing damage that affects their health. The shielded fighters are affected less than pavers and normal fighters.  

## Input File  
The application receives all the needed information about towers and enemies from an input file called **"input.txt"**.  

Input File Format:  
- First line contains three numbers: **TH N TP**  
**TH** is the starting health of all towers; **N** is the maximum number of enemies a tower can attack at one time step and **TP** is the tower fire power.  
- Second line contains three constants **C1 C2 C3** used to calculate the priority of shielded fighters as each tower shoots **N** enemies at each time step so the enemies with higher priority are shot first.  
- Third line contains the number of enemies in the input file.  
- Then the input file contains many lines (one line for each enemy) of the format:  
**ID ‏‏‎ ‎Type  ArrivalTime  Health  FirePower  ReloadPeriod  Region**  
where **ID** is a sequence number that identifies the enemy (must be unique), **Type** is the enemy type (0:paver, 1:fighter and 2:shielded), **ArrivalTime** is the enemy arrival time step, **Health** is the enemy health, **FirePower** is the enemy fire power, **ReloadPeriod** is the enemy reload period need between each successive attack time steps and **Region** is the enemy region. The input lines are sorted by **arrival time in ascending order**.  

  

