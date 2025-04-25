🕹️ **ALT+TAP - Stealth Mini Game**

Một trò chơi hành động lén lút hài hước, nơi bạn vào vai Tuấn, một cậu bé đang tìm cách trốn học để chơi game, và Mẹ Tuấn, người luôn rình mò kiểm tra bất ngờ để bắt quả tang con mình "phá phách". Trò chơi mô phỏng lại tình huống kinh điển của biết bao thế hệ học sinh Việt Nam – với phong cách hoạt hình vui nhộn, nhạc nền đặc trưng, và sự căng thẳng đến nghẹt thở mỗi khi... mẹ vào phòng!

VIDEO demo về game: https://drive.google.com/drive/my-drive?fbclid=IwY2xjawJrVXBleHRuA2FlbQIxMAABHu0ND9V9npkerHHuhIb5bA0qqYym43laq9SEUu3vWwO9ohcGzCBf27cUqvJ-_aem__QHM1SZb957ugrxH5FIIGQ

🧠 **1. Ý TƯỞNG**

ALT+TAP là một trò chơi mini thể loại stealth (lén lút) nơi bạn vào vai Tuấn, một cậu bé mê game nhưng bị mẹ cấm chơi khi đang học.

Bạn có thể lựa chọn:

Chế độ Con : Bấm chuột để chơi game, thả chuột để quay lại học bài. Nhưng cẩn thận, Mẹ có thể ghé qua bất cứ lúc nào!

Chế độ Mẹ : Quan sát và kiểm tra bất ngờ để bắt quả tang cậu con đang trốn học chơi game.

![Screenshot 2025-04-25 202214](https://github.com/user-attachments/assets/05a52e59-6ced-4e38-9cca-e2ea6eba21d6)


🎮 **2. CÁCH CHƠI**

**Chế độ Con :**

Giữ chuột trái để chơi game → tiến độ tăng.

Thả chuột để học bài → không bị mẹ phát hiện.

Thắng khi thanh tiến độ đầy (tức là chơi xong game).

Thua nếu bị mẹ bắt quả tang đang chơi.


![Screenshot 2025-04-25 205109](https://github.com/user-attachments/assets/853a2c13-ae19-444c-8cca-f3fa7d363a1c)




**Chế độ Mẹ :**

Nhấn chuột trái để đột ngột xuất hiện kiểm tra.

Nếu bắt được con đang chơi game → Thắng.

Nếu kiểm tra 5 lần mà không bắt được → Thua.

![Screenshot 2025-04-25 204428](https://github.com/user-attachments/assets/d530a9d9-d930-48ce-8f3b-dc5c65ec85ae)



🎮 **3. CÁC THÀNH PHẦN TRONG GAME:**


**TuanChoiGame:**
Đây là Tuấn – thanh niên đam mê chơi game như hơi thở. Bình thường học hành lờ đờ, nhưng cứ đến giờ cắm tai nghe vào là thao tác như thần. Trong game, cậu ấy chính là bạn – người điều khiển mọi ánh mắt, tay bấm và phản xạ siêu phàm để... không bị bắt.

![Screenshot 2025-03-23 143201](https://github.com/user-attachments/assets/30226c80-c1b4-4703-8320-737bb04f9a2f)


**TuanHocBai:**
Khi mẹ xuất hiện, Tuấn bật chế độ "con người ta", mặt đơ ra như đang làm toán nâng cao, nhưng thực ra trong đầu vẫn còn đang combat dở. Đây là pha ngụy trang cực kỳ quan trọng để sống sót qua mỗi lần kiểm tra.

![Screenshot 2025-03-13 155824](https://github.com/user-attachments/assets/366a3187-65bd-40c0-a11e-23b5a1609ab7)


**Mẹ Tuấn:**
Nhân vật phản diện quyền lực bậc nhất vũ trụ này. Mẹ không hiện ra từ trong khói như ninja, mà xuất hiện đột ngột kiểu: “Ủa, con đang làm gì đó?”. Mỗi lần mẹ vào kiểm tra là một lần tim rơi xuống dạ dày. Mẹ chỉ kiểm tra vài lần thôi, nhưng chỉ cần bắt gặp 1 lần là “End Game”.

![mom_stern](https://github.com/user-attachments/assets/5a2a7971-9a4b-41cd-aabf-e2b8aae53308)


**Thanh tiến độ chơi game:**
Càng chơi thì thanh này càng đầy. Khi nó đầy 100% mà chưa bị mẹ phát hiện → bạn win. Vừa chơi vừa lo bị bắt, cảm giác như vừa leo núi vừa né sấm sét.

**Âm thanh**
Có 2 loại:

Tiếng chơi game 

Tiếng học bài (phát ra để lừa mẹ rằng bạn đang “siêng”)


🛠️ **4. THÔNG SỐ KỸ THUẬT**

Ngôn ngữ: C++

Thư viện: SDL2, SDL_image, SDL_mixer

Nền phòng: room_background.png

Nhân vật:

TuanChoiGame.png

TuanHocBai.png

mom_stern.png

Nhạc nền:

Học bài: study.wav

Chơi game: choigame.mp3

💻 **5. SOURCE CODE OVERVIEW**
Toàn bộ mã nguồn được viết bằng C++ sử dụng thư viện SDL2, chia thành các chức năng rõ ràng cho từng vai trò: Tuấn và Mẹ Tuấn.

🧱 **File cấu trúc chính**

1. main.cpp – Giao diện chính & Điều hướng chế độ

Hiển thị menu nền (menu_background.png) và 2 nút chọn chế độ:

button_con.png: Vào vai Tuấn (Child)

button_me.png: Vào vai Mẹ (Mom)

Xử lý sự kiện click chuột chọn chế độ, gọi hàm tương ứng:

RunGameAsChild()

RunGameAsMom()

2. roleOfSon.h – Logic chế độ Con (Tuấn)

-Hàm chính: RunGameAsChild(SDL_Window* window, SDL_Renderer* renderer)
Vòng lặp chính xử lý:

Input: Nhấn/nhả chuột trái để chơi hoặc thả tay.

Progress bar: Tăng dần khi nhấn chuột.

Sự kiện mẹ vào phòng: Xác suất mẹ kiểm tra được tăng dần theo thời gian chơi.

-Các hàm phụ:

CapNhat(...): Cập nhật logic trạng thái game: mẹ đến, kiểm tra, tiến độ chơi.

VeManHinh(...): Hiển thị hình ảnh hiện tại:

Tuấn chơi hay học (dựa vào nhấn chuột).
Mẹ có đang vào không.
Thanh tiến độ game.

GameOver(): Khi bị bắt quả tang.

Victory(): Khi đạt 100% tiến độ mà không bị bắt.

Tài nguyên:
Ảnh: TuanChoiGame.png, TuanHocBai.png, mom_stern.png

Âm thanh: choigame.mp3, study.wav

3. roleOfMom.h – Logic chế độ Mẹ
Hàm chính: RunGameAsMom(SDL_Window* window, SDL_Renderer* renderer)

-Vòng lặp chính xử lý:

Nhấn chuột để kiểm tra con.

Mỗi lượt kiểm tra chỉ được 3 giây nhìn vào phòng.

Nếu bắt gặp Tuấn đang chơi, thắng.

Sau 5 lượt không bắt được, thua.

-Các hàm phụ:
Update(...): Đếm số lượt kiểm tra, random trạng thái Tuấn (học hay chơi).

Render(...): Vẽ mẹ vào hay không, trạng thái Tuấn lúc mẹ nhìn vào.

Lose() / Win(): Kết thúc game tùy theo kết quả kiểm tra.

4. InitSDL() & CloseSDL()
-InitSDL(): Load tất cả hình ảnh (vào texture), nhạc nền, khởi tạo SDL.

-CloseSDL(): Giải phóng tài nguyên, gọi:

-SDL_DestroyTexture, Mix_FreeMusic, SDL_DestroyRenderer, SDL_DestroyWindow, SDL_Quit(),...


---


😂 Bonus: Tại sao Tuấn lại như vậy? (Dựa trên một câu truyện được chứng kiến và kiểm chứng)
Tuấn là cậu bé đại diện cho một thế hệ – muốn giải trí, nhưng vẫn sống trong sự kiểm soát của phụ huynh. Game là lời tri ân đến những khoảnh khắc đầy hồi hộp đó, được gói gọn trong một thế giới pixel đầy yêu thương... và hơi nhiều la mắng.

Game được thiết kế nhằm nhắc nhở các bạn trẻ về tầm quan trọng của việc học hành và sự quan tâm từ gia đình. Tuy nhiên, mọi thứ đều được thể hiện thông qua một lăng kính nhẹ nhàng và vui nhộn, giúp người chơi nhận thức được vấn đề mà không cảm thấy quá áp lực hay nặng nề.
