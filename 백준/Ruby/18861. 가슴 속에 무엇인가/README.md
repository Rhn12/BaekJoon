# [Ruby V] 가슴 속에 무엇인가 - 18861 

[문제 링크](https://www.acmicpc.net/problem/18861) 

### 성능 요약

메모리: 60544 KB, 시간: 748 ms

### 분류

그래프 이론, 링크/컷 트리, 최소 스패닝 트리, 트리

### 제출 일자

2024년 7월 20일 15:28:44

### 문제 설명

<p>대문 밖을 나서고 입대가 초읽기로 다가오자, 초조해지는 마음에 욱제는 가슴을 마구 내리쳤다. 그러자 평소 심혈관계 건강이 좋지 않았던 욱제의 모세 혈관들이 모두 파열되어 버렸다.</p>

<p>젊은 욱제의 심혈관계는 1번부터 <em>N</em>번까지 번호가 붙은 <em>N</em>개의 세포와 서로 다른 두 세포 사이를 연결하여 혈액을 공급하는 혈관으로 표현할 수 있다. 몇 개의 혈관들을 통해 연결된 두 세포 사이에는 혈액이 흐를 수 있다. 욱제가 가슴을 마구 내리쳤기 때문에 처음에는 어떤 혈관도 남아있지 않다. 시간이 흐름에 따라 젊은 욱제의 혈관은 생성되고 터지기를 반복한다. 혈관 x의 강도는 한계 심박수 D<span style="font-size: 10.8333px;">x</span>로 표현되는데, 긴장한 욱제의 심박수가 D<span style="font-size: 10.8333px;">x</span>를 초과하면 이 혈관은 견디지 못하고 터져버린다. </p>

<p>계속 혈관이 생기고 터지면서 멍이 들자, 욱제는 세포들 사이에 혈액이 원활하게 공급되고 있는지 걱정되어 자가 진단 기계를 만들고자 한다. 즉, 욱제는 위에 주어진 3가지 쿼리를 처리하는 기계를 만들고자 한다.</p>

<ul>
	<li>1 i j d : i번 세포와 j번 세포를 직접 잇는 한계 심박수 d인 혈관이 생성된다. (i ≠ j) 두 세포 사이에 여러 개의 온전한 혈관이 동시에 존재하는 일은 없다.</li>
	<li>2 x : 욱제의 심박수가 순간적으로 x로 변화한다. 이 사건이 일어나는 시점 이외에 욱제의 심박수는 충분히 낮아 0으로 가정해도 좋다.</li>
	<li>3 i j : 이 쿼리가 주어진 시점에 i번 세포와 j번 세포 사이에 혈액이 흐를 수 있는 욱제의 최대 심박수 x를 출력한다. (i ≠ j)</li>
</ul>

<p>하지만 욱제는 계속 가슴을 내리치느라 손에 멍이 들어 코딩을 할 수가 없다. 여러분이 이 질문을 대신 처리해주도록 하자.</p>

### 입력 

 <p>첫째 줄에 세포의 개수 <em>N</em>과 쿼리의 개수 <em>Q</em>가 주어진다.</p>

<p>둘째 줄부터 <em>Q</em>개의 줄에 걸쳐 쿼리들이 입력으로 주어진다. </p>

### 출력 

 <p>3번 쿼리가 주어질 때마다 그에 대한 답을 출력한다. 해당 시점에 두 세포 사이에 혈액이 흐를 수 없다면 0을 출력한다.</p>

