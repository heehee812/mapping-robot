# :robot_face: Mapping Robot Algorithm

### Description
The goal of this project is to create a efficient path for robot to pass the whole area depends on different input.

### Main flow chart
![](https://i.imgur.com/iA07iBW.png)

### Algorithm
* component
    * Point
        * `pos` 記錄該點位子
        * `val` 記錄該點狀態（0 代表未被走過，1 代表是牆壁，2表走過)
        * `used` 用於搜尋最短路徑時判斷是否有迴圈的狀況。
        * `up`, `down`, `left`, `right` 記錄該點四周的點，判斷下一步該往哪裡走。
    * Floor
        初始狀態由指標floor指向Point所組成的二維陣列。
        
        **variable**
        * `readyQueue`: 記錄機器人周圍可以走的點。
        * `waitingStack`: 記錄機器人走過的點。
        * `enough`: 用於判斷電量是否充足。
        * `recordpath`: 最後印出的完整路徑
        **function**
        * `optimize_queue()`
            當點機器人移動到點ptr時，將呼叫`around_point()`周圍可以走的點放入`readyQueue`，並判斷該逆時針還是順時針走能走的步數比較多。
        * `around_point()`
            舉以下示意圖為例，*line70*，表方向從上開始，若`val`=0，則將該點放入`readyQueue`中，若`dir`= 1，表順時針方向繼續搜索可以放入`readyQueue`中的連續點，反之亦然。若`val`!= 0，表不能走，則判斷若`readyQueue`為空則依據dir判斷並往下一個方向搜索。
        * `update_floor()`
            判斷該點至下一點距原點的電量是否充足，若不充足，則利用`get_simplepath()` 去得最短路徑回去充電，再利用最短路徑回到要去的點。若充足，將`readyQueue`中所記錄的點一一放入`waitingStack`中，並把移動的點的`val`設為2，步數加一，電量減一。
        * `get_simplepath()`
            呼叫`simple_path()`記錄起點到終點所走的最短路徑。並回傳路徑之大小以當消耗的步數。
        *  `simple_path()`
            利用`priority_queue()`記錄該點至下一點優先走的方向，透過呼叫`get_dir()`判斷該方向是否可以行走，若可以則回傳行走過後的位置，若不行則回傳原本的位置。
            1. 判斷是否是否無路可走？是：結束遞迴，否：遞迴至下一個點。
            2. 判斷是否進入回圈？
                若該點之used= 1，則表示該點之前已經走過，則設布林值`duplicate`= 1，跳出遞迴至重複的點第一次出現的那層，並將`recordpath`中該迴圈清除。
            3. . 判斷是否抵達終點？
                將布林值`arrive`設為一，並呼叫`initialize_path()`初始化所有變數。
        * `priority_queue()`
            以下示意圖舉例，若終點在該點的右上方，則方向優先序則設為：右、上、左、下，但若該點非起點，則會根據從哪個方向來去除掉該方向，避免來回走以及回圈的出現。
        * `get_dir()`
            以下示意圖舉例，當方向為上，則判斷該點是否可以往上走，若可以，則判斷是否為牆，是的話回傳原本的點，不是的話回傳該點。
